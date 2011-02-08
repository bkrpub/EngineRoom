
** this documentation does not yet exist ** work in progress **

Using EngineRoom in your Application
------------------------------------

Recommendations:
	Put the EngineRoom folder beneath your project folder.
	Use a shared build directory (Xcode -> Preferences -> Building)

These instructions are for use with the above setup.
Not using a shared build directory will need more project adjustments.

Now open your project, select the project itself and choose
Add -> Existing files.

Navigate to

OSX: EngineRoom/EngineRoom-OSX and choose EngineRoom-OSX.xcodeproj
iOS: EngineRoom/EngineRoom-iOS and choose EngineRoom-iOS.xcodeproj

Do not tick "Copy".

On opening the new entry it should reveal 

OSX: EngineRoom.framework
iOS: libEngineRoom.a

OSX: Create a new Copy Files Build Phase with target "Frameworks" and drag the
     framework to it (from the EngineRoom project).

     Option-Drag the framework from there to your targets 'Link Binary with Libraries'.

iOS: Drag the libEngineRoom.a from the EngineRoom project to your targets 'Link Binary with Libraries' 

Open the inspector for your target, Tab "General", 
add EngineRoom-OSX as a dependency.

iOS: Add '-all_load' and '-ObjC' to 'Other Linker Flags'
     (needed to load the ObjC classes and the initFunction)

OSX: Open your MainMenu NIB and add an NSObject, set its class to EngineRoom,
     this will provide you with a LogPoint Menu.
     If you prefer a MenuItem, add one and connect EngineRoom's engineRoomMenuItem outlet to it.
     And try clicking the item.


I recommend adding 

--- 8< ---

#import <EngineRoom/EngineRoom.h> 
#import <EngineRoom/logpoints_default.h>

// useful for testing - makes your NSLog()s into logpoints
#import <EngineRoom/logpoints_nslog.h> 

--- >8 ---

to your prefix header (Other Sources -> YourProject_Prefix.pch)

Now recompile and run.

On OSX: 
   hit Option-Command-.
   You can enter predicates in the textfields to activate LogPoints.

   There is shorthand available - still a moving target - therefore undocumented:

   but here is an example:

   if you enter:

   :selectorPrefix ; @ClassPrefix ; #keyword ; ?drag

   EngineRoom will activate LogPoints matching the following predicate:

   ( symbolNameOrSelectorNameForDisplay BEGINSWITH 'selectorPrefix' ) OR 
   ( className BEGINSWITH 'ClassPrefix' ) OR 
   ( keys CONTAINS 'keyword' ) OR 
   ( formatInfo CONTAINS 'drag' )

   formatInfo is (more or less) the format string you gave to your log message.


The startup filter is written to your apps user defaults and can be modified like this:

$ defaults write your.app.identifier logPointFilter '...'

$ defaults write your.app.identifier logPointDump -bool YES

will produce a dump of all logpoints for testing purposes

Both of these keys can be included in your Info.plist to be used
as a fallback if no defaults are set.

iOS: 
     The last paragraph above is the way to set filters for now.
     


Useful hints:

In Xcode, double click on the opening bracket of <file:lineno> and
hit Cmd-Shift-Opt-D (Open this quickly).
(This does not work if a Find Panel is active - close it)

Performance:
Since EngineRoom is under active development, 
it has all optimization turned off for the Debug Configuration.


Credit: 
http://ancientbuho.posterous.com/xcode-logging-trick-quickly-open-a-logs-locat

