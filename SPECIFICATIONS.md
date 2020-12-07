# Project specifications

> [School subject](doc-files/requirements.pdf)

## Parser definition

![Parser](doc-files/parser.svg)

## List of requirements

- [ ] **FEAT-1**: Manage variables
  - [ ] **-VAR-1**: affect value: `var=word` (RegEx: `[WORD]=[WORD]`)
  - [ ] **-VAR-2**: affect value: `var="string"` (RegEx: `[WORD]=[STRING]"`)
  - [ ] **-VAR-3**: access value: `$var`
- [ ] **FEAT-2**: Parse command
  - [ ] **-PARSE**: space character used as command line delimiter, except inside string (`" "`)
- [ ] **FEAT-3**: Execute command
  - [ ] **-INT-CMD**: internal command
    - [ ] **-ECHO**: `echo`
    - [ ] **-PWD**: `pwd`
    - [ ] **-PATH-1**: `showpath`
    - [ ] **-PATH-2**: `addpath [path]`
    - [ ] **-PATH-3**: `delpath`
  - [ ] **-EXT-CMD**: External command (available in system tree)
    - [ ] **-SEARCH-1**: determined by absolute path
    - [ ] **-SEARCH-2**: determined by internal variable path research
    - [ ] **-ERROR**: return **error** message for unavailable command
- [ ] **FEAT-4**: Output redirection
  - [ ] **-REDIR-1**: `>`: redirect output to file (overwrite)
  - [ ] **-REDIR-2**: `>>`: redirect output to file (append)
  - [ ] **-REDIR-3**: `|` "pipe": redirect left command output to right input command
- [ ] **FEAT-5**: Background task
  - [ ] **-BACKG**: `&`: Create background task
