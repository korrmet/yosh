# yosh
tiny shell for microcontrollers
```
YOctoSHell v0.0a
 .::::::.     + +       
.::::::::.   +---- | | |
:::::::: .\  +---- | | |
::::::::_,_o +---- +-+-|
```
# Licence
Licenced by APL:
Asshole Public Licension:
If you use this code without telling your buddies what you got it on 
github.com/Korrmet - you're an asshole. Come on, don't be asshole!

# Motivation
I'm often think doing my job if i can do somethig after firmware is loaded
inside microcontroller. In example what if i can dynamically change some
variable or reinitialize interface. Ofcourse i can do it when i debugging but
often we needs some extra features. If you try to google something about
shell for microcontrollers you will see what it's rare thing. In my opinion
authors of these shells has aim to implement standard unix/posix shell on
hardware and it's is large job. I try to implement very basic and tiny shell
but useful. I'm don't shure what so basic console needs to be full unix clone
and i can't realize any task for it. But tasks such as turning stepper motor
to an angle from uart input or get log of errors are usual. In my opinion
it's enough for develop own shell which i can use in my job.

# Status
Just start developing but usable.

# Project structure
Architecture of this project close to microkernel. There is core which provide
main features and some isolated plugins. Also core has dependencies on code
which provide common behavour for multiple projects.

```
. . . . . . . . . . . . . . . . 
.                             .
. +-------+ +------+ +------+ .
. | about | | help | | exit | .
. +-------+ +------+ +------+ .
.     |         |        |    .
.     +---------+--------+    .
.               |             .
.          +---------+        .            +------------+
.          | builtin |        .            | containers |
.          +---------+        .            +------------+
.               |             . . . . . .        |
.               +-----------------+--------------+
.                                 |     .
.                             +------+  .
.                             | Core |  .
.                             +------+  .
.                                       .
. . . . . . . . . . . . . . . . . . . . .
```

On drawing dotted area represents kernel. Also Core have interface for user
applications which can be connected in runtime. Entities outside of dotted area
are submodules. Nowdays it's not clearly isolated tools and you can't easily
use cuctom of it because their interface used directly inside core entities, but
it will be fixed soon.

Yosh distributed as library, but it used another not so popular library. So in
distributive yo will see containers library distributive which you can use if
you wish. But if you want use yosh you must link it in your project. Nowdays
this library is present as part of this repo, but soon it will have it's own
repo with many cool stuff for c-programmers. I think you will like it.

Also for testing purposes this repo contains another library called dumbtools.
It contains minimalistic and unsafe versions of memcpy, memcmp and another
similar staff which may be effectively used in tiny microcontroller
applications. This is also important library which will have it's on repo too.
It will be grow and soon you see two versions of malloc in it.

# Build
```
make release
```

or

```
make debug
```

# Testing
At present day it has only sandbox. It is not test but so close so i decided
include it in testing folder. In common to run test you need:

```
make sandbox
```

At present day i have not unit tests.

# Versions
Versions are represents by template:

v<major>.<minor><letter>

There <major> increments when all current sprint requirements are closed.
<minor> version increments when one of requirements being closed or when bug
fixed. Letter represents workaround of every minor incrementation. It may be
'r', 'a' or 'd'.

'r' letter means release, 'a' means pre-release, and 'd' means debug. Release
version is fully tested and works, pre-release version must build and partially
tested, debug version may not build and have no test but it tell us what code
was written and now it prepare for become pre-release.

# Branches
This repo contains many branches but two of them are special. 'master' contains
only release versions. 'devel' contains pre-release and debug versions. Another
branches are temporary and sometimes may be deleted (i didn't decide when it
may happens but in my opinion it must be close to increment of major version).

# Plans
b4 v1.0r will be released next requirements must be closed
- ( 0) [x] (won't do it) implement output redirect to another command
           I think it's not necessary requirement. This shell is not
           replacement.
- ( 1) [ ] implement braces for manual argument borders
- ( 2) [ ] implement retval handling
- ( 3) [ ] implement shell variables extraction
- ( 4) [ ] implement shell login
- ( 5) [x] (won't do it) implement adding user commands in running shell
           I think it's not necessary requirement. This shell is not
           replacement.
- ( 6) [ ] make tests
- ( 7) [ ] complete readme
- ( 8) [v] make doxygen comments in code
- ( 9) [ ] white documentation and guidelines about using this shell
- (10) [v] fix dependencies
- (11) [ ] add automatic version mark
- (12) [v] separate containers library
- (13) [v] separate dumbtools library
- (14) [ ] develop build mechanisms

# Tracability matrix
| requirement | version | commit  | test | file/folder               |
| ----------- | ------- | ------- | ---- | ------------------------- |
|  0          | v0.1d   | cfc243e | N/A  | README.md                 |
|  1          |         |         |  -   |                           |
|  2          |         |         |      |                           |
|  3          |         |         |      |                           |
|  4          |         |         |      |                           |
|  5          | v0.1d   | cfc243e | N/A  | README.md                 |
|  6          |         |         |      |                           |
|  7          |         |         |      |                           |
|  8          |         |         |      |                           |
|  9          |         |         |      |                           |
| 10          | v0.1d   | cfc243e | N/A  | ./                        |
| 11          |         |         |      |                           |
| 12          | v0.1d   | cfc243e | N/A  | ./containers              |
| 13          | v0.1d   | cfc243e | N/A  | ./tests/sandbox/dumbtools |
| 14          |         |         |      |                           |
