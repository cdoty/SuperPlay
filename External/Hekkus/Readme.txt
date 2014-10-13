This folder contains Hekkus Sound System:
http://www.shlzero.com/wordpress/?page_id=4

Create an include folder and drop HSS.h and the include folder into the created include folder.
Drop the lib_static folder into this folder.

The layout should look like this:

Hekkus
+->include
   HSS.h
   +->include
+->lib_static

If you are using Visual Studio 2010/2012, you may need to either recompile the library or
use rc9 instead of the latest release.
