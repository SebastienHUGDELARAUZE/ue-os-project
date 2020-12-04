# Project specifications

## Parser definition

![Parser](doc-files/parser.svg)

## List of requirements

- [ ] **FEAT-1**: managed variables
  - [ ] **VAR**: affect value: `var=string`
  - [ ] **VAR**: affect value: `var="composed string"`
  - [ ] **VAR**: access value: `$var`
- [ ] **FEAT-2**: parse command
  - [x] **PARSE**: ` ` "space": command line delimiter, except inside string (`" "`)
- [ ] **FEAT-3**: execute command
  - [ ] **EXEC-CMD**: internal command
    - [ ] **INT-CMD**: `echo`
    - [ ] **INT-CMD**: `pwd`
    - [ ] **INT-CMD**: `addpath [path]`
    - [ ] **INT-CMD**: `delpath`
    - [ ] **INT-CMD**: `showpath`
  - [ ] **EXEC-CMD**: external command (available in system tree)
    - [ ] **EXT-CMD**: Determined by absolute path
    - [ ] **EXT-CMD**: Determined by internal variable path research
    - [ ] **EXT-CMD**: Return error message for unavailable command
- [ ] **FEAT-4**: Output redirection
  - [ ] **REDIR**: `>`: redirect output to file (overwrite)
  - [ ] **REDIR**: `>>`: redirect output to file (append)
  - [ ] **REDIR**: `|` "pipe": redirect left command output to right input command
- [ ] **FEAT-5**: Background task
  - [ ] **BACKG**: `&`: Create background task
