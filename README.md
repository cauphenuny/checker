# Checker
A useful and convenient checker for OI. (**compatible version**, no GNU-readline)

## Install
```bash
./install.sh
checker -h
```

## Usage:
```
checker [$problem_name] [-vlcqfuh] [--save=] [--branch=]

-h: display this help and quit
-f: fast mode
-c: always continue when error occurs
-q: always quit when error occurs
-v: check version and quit
-u: update

--save=auto  : save file only when error occurs (default)
       always: always save input and output file
       never : never save file

--branch=master    : default branch
         dev       : developing branch, new and experimental
         compatible: compatible branch, for older OS, without GNU-readline
```

---
Current version: 5.5  
Supported operating system: Ubuntu 16.04 or later.
