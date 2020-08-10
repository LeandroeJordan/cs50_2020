import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

db.execute('''
    CREATE TABLE IF NOT EXISTS 'balances' (
    'id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    'user_id' INTEGER NOT NULL,
    'symbol' TEXT NOT NULL,
    'shares' INTEGER NOT NULL,
    FOREIGN KEY(user_id) REFERENCES users(id)
)
''')
db.execute("CREATE UNIQUE INDEX IF NOT EXISTS unique_balances_user_id_symbol ON balances (user_id, symbol)")

db.execute('''
CREATE TABLE IF NOT EXISTS 'history' (
    'id' INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    'user_id' INTEGER,
    'symbol' TEXT,
    'shares' INTEGER NOT NULL,
    'price' NUMERIC NOT NULL,
    'create_at' DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY(user_id) REFERENCES users(id)
)
''')
db.execute("CREATE INDEX IF NOT EXISTS index_history__user_id ON history (user_id)")


# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    users = db.execute("SELECT * FROM users WHERE id = ?", session['user_id'])
    user = users[0]
    rows = db.execute('SELECT * FROM balances WHERE user_id=?', session["user_id"])
    stocks = []
    totalg = 0.00
    for row in rows:
        stock = row
        stock_details = lookup(stock["symbol"])
        stock['price'] = stock_details['price']
        stock['total'] = stock_details['price'] * stock['shares']
        totalg += stock['total']
        stock['name'] = stock_details['name']
        stocks.append(stock)
    return render_template("index.html", totalg=totalg, cash=user['cash'], stocks=stocks)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Missing Symbol", 400)
        if not request.form.get("shares"):
            return apology("Missing Symbol", 400)
        elif not request.form.get("shares").isdigit():
            return apology("Invalid shares value", 400)

        symbol = request.form.get("symbol").upper()
        stock = lookup(symbol)

        if stock == None:
            return apology("Invalid Symbol", 400)

        # Query database for username
        rows = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        cash = rows[0]["cash"]
        shares = int(request.form.get("shares"))
        new_cash = cash - shares * stock['price']

        if new_cash < 0:
            return apology("You dont have enough cash", 400)

        # Update a new_cash balance to users
        rows = db.execute("UPDATE users SET cash = :new_cash WHERE id = :id",
                            new_cash = new_cash , id=session["user_id"])

        # Query to verify balance exists
        rows = db.execute("SELECT *  FROM balances WHERE user_id = ? and symbol = ?", session["user_id"], symbol)
        if len(rows) < 1:
            # Insert new balance
            db.execute("INSERT INTO balances (user_id, symbol, shares) values (?, ?, ?)", session["user_id"], symbol, shares)
        else:
            newbalance = rows[0]
            newbalance['shares'] += shares
            #Update balance after Buy
            db.execute("UPDATE balances set shares = ? where id = ?", newbalance['shares'], newbalance['id'])

        #Insert history
        db.execute("INSERT INTO history (user_id, symbol, shares, price) values (?, ?, ?, ?)", session["user_id"], symbol, shares, stock['price'])
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    rows = db.execute('SELECT * FROM history WHERE user_id=?', session["user_id"])
    results = []
    for row in rows:
        item = row
        item['total'] = item['price'] * item['shares']
        results.append(item)
    return render_template("history.html", results=results)



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Missing Symbol", 400)
        symbol = request.form.get("symbol").upper()
        stock = lookup(symbol)
        if stock == None:
            return apology("Invalid Symbol", 400)
        return render_template("quoted.html", stock=stock)
    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        # Ensure username was submitted

        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)
        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("Passsword and confirmation password must be the same", 403)

        # if username, password and confimation OK
        primary_key = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                        username=request.form.get("username"),
                        hash=generate_password_hash(request.form.get("password")))
        if primary_key is None:
            return apology("Resgistration Error. Please Check if username already existes.", 403)
        session["user_id"] = primary_key
        return redirect("/")
    else:
        return render_template("register.html")

#  """Register user"""
#    return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Missing Symbol", 400)
        if not request.form.get("shares"):
            return apology("Missing Symbol", 400)
        elif not request.form.get("shares").isdigit():
            return apology("Invalid shares value", 400)

        symbol = request.form.get("symbol").upper()
        shares = int(request.form.get("shares"))
        stock = lookup(symbol)

        if stock == None:
            return apology("Invalid Symbol", 400)
        balances = db.execute("SELECT *  FROM balances WHERE user_id = ? and symbol = ?", session["user_id"], symbol)
        if len(balances) < 1:
            return apology("You dont have any shares of this stock", 400)
        elif balances[0]['shares'] < shares:
            return apology("You dont have shares enough", 400)

        #If everything is ok
        # Query database for username
        rows = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        cash = rows[0]["cash"]
        #shares = int(request.form.get("shares"))
        new_cash = cash + shares * stock['price']

        if new_cash < 0:
            return apology("You dont have enough cash", 400)

        # Update a new_cash balance to users
        rows = db.execute("UPDATE users SET cash = :new_cash WHERE id = :id",
                            new_cash = new_cash , id=session["user_id"])


        balances[0]['shares'] = (balances[0]['shares'] - shares)
        #Update balance after Buy
        db.execute("UPDATE balances set shares = ? where id = ?", balances[0]['shares'], balances[0]['id'])

        #Insert history
        db.execute("INSERT INTO history (user_id, symbol, shares, price) values (?, ?, ?, ?)", session["user_id"], symbol, (shares * -1), stock['price'])
        return redirect("/")
    else:
        stocks = db.execute("SELECT * FROM balances WHERE user_id = ? and shares > 0", session["user_id"] )
        return render_template("sell.html", stocks=stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
