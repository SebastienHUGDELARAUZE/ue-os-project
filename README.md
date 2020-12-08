# SHELL Project

![CI for OS-Project](https://github.com/SebastienHUGDELARAUZE/ue-os-project/workflows/CI%20for%20OS-Project/badge.svg?branch=master)

> Based on C99 & Linux.  
> Maintainer: Sébastien HUG DE LARAUZE ([GitHub](https://github.com/SebastienHUGDELARAUZE/ue-os-project))  
> Educator: Eric TOTEL (IMT Atlantique)

## Usages

- To build the project, you can use the makefile task `build`:

      $ make build
      gcc ...

  > Will produce an executable called `main`

- To clean the project afterward, use the task `clean`:

      $ make clean
      rm ...

## Shell specifications

[See SPECIFICATIONS](./SPECIFICATIONS.md) file.

## Test specifications

[See SPECIFICATIONS-TEST](./SPECIFICATIONS-TEST.md) file.

## Process

1. Lexical analysis
   - **Flex file:** Recognize all tokens
   - **Bison file:** Dummy logic (Accept all tokens)
     - _Action:_ Display tokens
2. Syntax analysis
   - **Bison file:** Write complete grammar
     - _Action:_ Display token reduction
3. Semantic analysis
   - Build/Calculate useful data
4. Error recovery

## Notes

Sources:

- [Python module: subprocess manager **Pexpect**](https://pexpect.readthedocs.io/en/stable/index.html)
- [Python module: test framework **PyTest**](https://docs.pytest.org/en/stable/contents.html)

Files of interest:

    > grammar.y         // Parser (GNU Bison)
    > syntax.flex       // Scanner (Flex)
    > shell.c           // SHELL program (source)
    > shell.h           // SHELL program (header)

Documentation on Bison and Flex:

- [Bison documentation](https://www.gnu.org/software/bison/manual/bison.html)
- [Flex documenation](http://gensoft.pasteur.fr/docs/flex/2.6.1/index.html)

Regular expression:

- [Regex101](https://regex101.com/)
- [Railroad diagram](https://regexper.com/)

Tutorials:

- [1. Flexible Bison: Compiler Theory - DONE](https://starbeamrainbowlabs.com/blog/article.php?article=posts/258-Languages-and-Compilers-Intro.html)
- [2. Compilers 101: Build your own flex + bison compiler in a few easy(?) steps](https://starbeamrainbowlabs.com/blog/article.php?article=posts%2F267-Compilers-101.html)
- [3. Introducing Flex and Bison](https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html)
- [4. Flex and Bison in C++](http://www.jonathanbeard.io/tutorials/FlexBisonC%2B%2B)
- [X. Our simple calculator: now using flex to generate the scanner - READ](https://www.usna.edu/Users/cs/lmcdowel/courses/si413/F10/labs/L04/calc1/ex1.html)
