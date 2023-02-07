To create your own plugin:

1. Copy the "example" folder.
2. Rename the copied folder and "example.vcxproj" to the name of your plugin. Delete "example.vcxproj.user" if it exists.
3. Open "Dragonade.sln". Right click the "Dragonade" solution and goto Add -> Existing Project. Navigate to the new folder you copied and click the 
   vcxproj file.
4. Read the comments in "da_example.cpp" for an explanation on many of DA's mechanics.
5. Compiled plugins will be named "da_<name>.dll". Add these to the [Plugins] section of da.ini to load them into your server.