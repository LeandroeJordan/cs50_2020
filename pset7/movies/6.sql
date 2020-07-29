select avg(rating) as "average rating" from movies m
    join ratings r on m.id = r.movie_id where m.year = 2012;