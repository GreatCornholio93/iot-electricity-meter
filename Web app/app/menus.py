from menu import Menu, MenuItem
from django.core.urlresolvers import reverse
# Add two items to our main menu
#Menu.add_item("main", MenuItem("Tools",
#                               reverse("myapp.views.tools"),
#                               weight=10))

Menu.add_item("main", MenuItem("Home", reverse("index"),weight=20))
Menu.add_item("main", MenuItem("DOCs", reverse("doc"), weight=20))
Menu.add_item("main", MenuItem("Devices", reverse("devices"), weight=20))


