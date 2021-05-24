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
github.com/Korrmet - you're an asshole.

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
.          +---------+        .        +-----------+ +------------+
.          | builtin |        .        | dumbtools | | containers |
.          +---------+        .        +-----------+ +------------+
.               |             . . . . . .    |             |
.               +-----------------+----------+-------------+
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

# Plans
- implement output redirect to another command
- implement braces for manual argument borders
- implement retval handling
- implement shell variables extraction
- implement shell login
- implement adding user commands in running shell
- make tests, readme and doxygen comments in code
- white documentation and guidelines about using this shell
- fix dependencies interfaces
