
![Icon](https://github.com/bkrpub/EngineRoom/raw/master/Resources/screenshot_free.png "Screenshot of LogPoint selector") 

**EngineRoom** is a toolkit addressing basic, recurring needs when
writing applications in C based languages.

The most mature part is a logging facility designed after many years of
using and trying to improve various logging mechanisms.

EngineRoom is targeted at *ix development with a focus on OS X and iOS.

The logging core has compiler and object file dependencies,
it works with gcc, clang (and sun cc) on Darwin, ELF-based GNU/Linux and Solaris.
The Linux and Solaris versions are pretty raw at the moment.

The iOS port is usable but needs more work.

LogPoints are built on three basic ideas:

* **Creating a well formed log message should require less effort than a sloppy one.**

        lpdebug(anInt, aRect, anObject); /* ObjC */
            HH:MM:SS.sss DEBUG 1 -[Class sel] anInt: 42 $0x2a ~ aRect: {{0,0}{0,0}} anObject: description realClass:addr <file:line>

	(with the format being configurable at runtime) instead of

        NSLog(@"%ld %@ %@", (long)anInt, NSStringFromRect(aRect), anObject);
            YYYY-mm-dd HH:MM:SS.sss Application [pid:tid] 42 {{0,0}{0,0}} description 

* **Log messages are powerful tools which complement debuggers.**

  More is better, but only if you can restrict output to what **you** are interested in **right now**.

  * Log levels are not sufficient to achieve this goal

  * LogPoints are selectively enabled using filter expressions
  which can target implicit metadata like file/class/function/line,
  explicit metadata (optional keywords) or (static) parts of the message itself.
  This avoids code bureaucracy and still provides for much flexibility in selecting messages.

* **A developer should be able (if desired) to ship a fully instrumented build without sacrificing performance**

  * The time required to decide which messages are enabled
  is spent once when the filter expression is set. 
  Afterwards, the overhead is a test of one bit.
  On a 2.5GHz MacBook Pro this is ~1ns per disabled logpoint.


* **The guts**	       
	  
  LogPoint macros are expanded to code that creates a static structure
  containing metadata and (besides others) an enabled flag.

  Because these structures are placed in a separate linker segment
  they can be located and manipulated at runtime.
  
  This mechanism is implemented for OS X / iOS Mach-O format and for 
  ELF on Linux and Solaris, in both 32 and 64bit variants.

This is achieved by creating a static structure in a separate linker segment
for each LogPoint which can then be accessed at runtime.



extensive use of the dynamism and introspective capabilities of Objective-C.

The logging component was ported to GNU/Linux and Solaris (gcc and sun cc) as well
but is not currently maintained.

EngineRoom targets *ix environments using gcc or clang compilers
with emphasis on OS X and iOS development.


* **Roadmap**

 * an [NSLogger](http://foo) backend is one of the next steps

The basic idea is to make the log message a first class citizen.
LogPoints are data structures which can be manipulated (i.e. enabled / disabled) at runtime.


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


