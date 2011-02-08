
What?

EngineRoom is a framework designed to free you from some of the chores of application development.

Component: logpoints

Logpoints are a logging and debugging facility for C based languages with strong support
for the dynamism and introspective capabilities of Objective-C.

Logpoints are built on three basic ideas:

	  * log messages are powerful tools which complement debuggers

	  * the more the better - but only if you need them

	  * team friction due to log message congestion is to be avoided

	  * one should be able (if desired) to ship a fully instrumented build
	    without sacrificing performance.
	  

The basic idea is to make the log message a first class citizen.
LogPoints are data structures which can be manipulated (i.e. enabled / disabled) at runtime.
This is achieved by creating static structures in a separate linker segment.

Debug messages are off by default - developers enabled those they currently need by
specifying a filter.


See HOWTO.txt for usage instructions.


Now for the commercials:

	       * just type what you want to see - no (mandatory) format strings, %ld's and casts to long

	       	      Number of arguments and their types can be detected and formatted accordingly:
	       	      
		        NSWindow *mainWindow = [NSApp mainWindow];

			lpdebug( mainWindow.title, mainWindow.frame, [[NSApp orderedDocuments] count] );


	       * no tools needed, one framework, one #import

	* team friendly

	       * silence is golden - debug messages default to "off"

	       * every developer enables his own set of messages

	       * working sets can be passed on in form of predicates and written to user defaults

	* dynamic

	       * messages (called logpoints) are data structures - objects even - your app can manipulate them

	       * runtime switchable using predicates on class, method, file, keywords and more

	       * conditional code execution based on enabled logpoints (i.e. debug drawing)

	* high performance - designed to be able to ship fully instrumented builds to testers (or end users)

	       * overhead for a runtime-disabled message is a single bit test a ~1ns on a 2.5GHz MacBook Pro


