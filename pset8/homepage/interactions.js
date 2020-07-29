const navbarButton = document.querySelector(".navbar-toggler");

navbarButton.addEventListener("click", toggleMenu);

const TOGGLE_SHOW_CLASS = "show";

function toggleMenu() {
  const menuId = navbarButton.getAttribute("data-target");
  const menu = document.querySelector(menuId);

  let isShowing = false;
  for (const classItem of menu.classList) {
    if (classItem === TOGGLE_SHOW_CLASS) {
      isShowing = true;
      break;
    }
  }

  if (isShowing) {
    menu.classList.remove(TOGGLE_SHOW_CLASS);
  } else {
    menu.classList.add(TOGGLE_SHOW_CLASS);
  }
}