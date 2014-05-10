cppxmlrpg
==========

A text-based RPG written (coded) in C++ using the CodeBlocks IDE and the TinyXML2 library.

Default Quest story written by me, Josh Maines, for the purpose of testing code.
You may edit the default.xml file for your own purposes, but I recommend creating
your own xml file and changing the string value in the LoadFile function call.
This will allow you to apply updates from the repository without losing your data.
In the future, I plan to add a stories list as a start screen.

Current functionality:
- Loads default.xml as the quest data.
- Allows for a variety of XML-based functions.
- Takes user input for a character name.

Try it out!

Upcoming features:
- Ability to add stories to a main menu!
- Graphical menu! (Only for the menu, not the game.)
- full-screen GUI! (Still text-based, though.)

Required libraries:
- TinyXML2 for XML loading and parsing. (zlib license)
