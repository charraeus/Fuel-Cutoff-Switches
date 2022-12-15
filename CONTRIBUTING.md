# Contributing {#contribute}

@tableofcontents

## tbd

@todo Add more conventions 

## Development Environment with Visual Studio Code

### Visual Studio Code

"IDE" with the following VSCode extensions:

* For Arduino programming: [***PlatformIO IDE***][vsc-01]
  This makes the installation of the Arduino development environment *no longer* necessary.
* For documentation:
  * Display docu as popup: [***Doxygen Documentation Generator** by Christoph Schlosser*][vsc-04]
  * Markdown support:
    * [***Markdown Preview Enhanced** by Yiyi Wang*][vsc-06]
    * [***Markdown Preview Mermaid Support** by Matt Bierner*][vsc-07]
* GIT version control:
  * [***GitLens - Git supercharged** by GitKraken*][vsc-12]
  * [***Git History** by Don Jayamanne*][vsc-13]

**Configuration**

The configurations of the extensions are stored in the `.vscode` directory.

[vsc-01]: (https://docs.platformio.org/en/latest/) "PlatformIO IDE on Visual Studio Marketplace"
[vsc-04]: (https://www.doxygen.nl) "Doxygen website"
[vsc-06]: (https://github.com/shd101wyy/markdown-preview-enhanced) "Markdown preview enhanced on github.com"
[vsc-07]: (https://marketplace.visualstudio.com/items?itemName=bierner.markdown-mermaid) "Markdown preview mermaid support on github.com"
[vsc-12]: (https://marketplace.visualstudio.com/items?itemName=eamodio.gitlens) "Gitlens - GIT supercharged on Visual Studio Marketplace"
[vsc-13]: (https://marketplace.visualstudio.com/items?itemName=donjayamanne.githistory) "Git History on the Visual Studio Marketplace"

### Git

For version management. Installation on the Mac is done using Homebrew, which of course must be installed.
```shell
brew install git
```

On [**Github**](https://github.com/CHarraeus/Fuel-Selector-Switch) there is a corresponding repository that contains all the files necessary for the project.

**Notes**

* *main* (the obsolete designation *master* is not used) contains the latest, executable version of the entire repository at all times.
* Further development takes place exclusively in the *development* branch and other *branches*.
* Minimum settings
  ``console
  $ git config --global user.name "firstname lastname "
  $ git config --global user.email firstname.lastname@example.com
  $ git config --global init.defaultBranch main
  ```

Link to [GIT doc](https://git-scm.com/book/de/v2).

### Doxygen with additional software

For generating source code docs. The installation on the Mac is done with Homebrew, which of course has to be installed. See also here: https://www.doxygen.nl.
To be able to include [*mermaid*][mermaid] diagrams, the [*Command-line interface (CLI) for mermaid*][mermaid-cli] is needed.

```shell
brew install doxygen
brew install mermaid.cli
```

[mermaid]: https://github.com/mermaid-js/mermaid "mermaid on github.com"
[mermaid-cli]: https://github.com/mermaid-js/mermaid-cli "mermaid-cli on github.com"

**Configuration**

* *Doxygen* is configured via the configuration file `Doxygen`, which is located in the project directory.

## style guides

* C++
  * [Google C++ Style Guide][stg-01]
  * [Google C++ Linter `cpplint`][stg-02]

[stg-01]: https://google.github.io/styleguide/cppguide.html
[stg-02]: https://google.github.io/styleguide/xmlstyle.html


Translated with www.DeepL.com/Translator (free version)