# Arduino PacMan
## Gabriele Cavallo

*Arduino PacMan* is a simple tool that simplifies the activities of sharing Arduino projects. Arduino projects usually have some sources (1 or more files) and a series of libraries that the project uses. There are lots of different libraries that we can use in our project, and this makes their managing less simplier.
Libraries have also different versions, and there are differces between this versions.
When we try to share a project, we usually post his code on <b>GitHub</b> or similars, and say witch libraries are used.
But this is not the best way.
The first goal of Arduino PacMan, is to create a complete tool that packages the project sources and the used libraries into one file. It also covers the installation phase: it creates a script to install the libraries in the correct position in the host computer.
When you will have to share your project, you will can just download the package, run the installation script, and... Code!!

## Main features
  * Source dependency check and listing
  * Sources managing
  * Library importing from search paths
  * Packages exporting
  * Multi-tab managing
  * Installation script generating

## Project organizing:
  * The branch <b> functional </b> contains all the most recent modifies and implementations, included unstable ones.
  * The branch <b> master </b> contains the stable version of <i>ArduinoPacMan</i> (the one with less bugs)

## Operating system compatibility:
  Arduino PacMan is written to be executed in the same way on Linux, Windows and MacOs. This is because it uses C++ and the Qt framework, that are cross platform. For additional informations of how to build code see the file <b>documentation/build.txt</b>
  If you have Windows, the oldest supported version is Windows 7.

## Documentation
  All the documentation of ArduinoPacMan is available as a series of html pages in the folder <b>documentation</b> <br>
  It covers the project structure, the settings managing and the compiling of the source code. Specific informations about versions and libraries used by the project can be found in the file <b>documentation/build.txt</b>

## Licence
  All the code in this project is open source, feel free to modify it, fork it, and also, if you want, to commit changes to the main repository. All the code is licenced under the LGPLv3 license.
  For more informations visit the Qt official website <b>https://www.qt.io/licensing/</b>
## Contacts
  For more informations about the project do not esistate to contact me at <b>gabri.cabal@gmail.com</b> and don't forget to put in the mail object the string <b>ArduinoPacMan</b>.
