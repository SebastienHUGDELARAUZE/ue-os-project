# https://github.com/tabatkins/railroad-diagrams/blob/gh-pages/README-py.md

import sys, os
import railroad as rr

########################################################################

def main():
    Parser().create_diagram()

########################################################################

class Parser:
    echo_cmd = rr.Sequence(
        "echo",
        rr.Choice(0,
            rr.NonTerminal("PATH"),
            rr.NonTerminal("STRING"),
            rr.Comment("COMMAND")
        )
    )

    pwd_cmd = rr.Terminal("pwd")

    showpath_cmd = rr.Terminal("showpath")

    addpath_cmd = rr.Sequence(
        "addpath",
        rr.NonTerminal("PATH"),
    )

    delpath_cmd = rr.Terminal("delpath")

    internal_cmd = rr.Group(
        rr.Choice(0,
            echo_cmd,
            pwd_cmd,
            showpath_cmd,
            addpath_cmd,
            delpath_cmd,
        ),
        "internal_cmd"
    )

    ########################################################################

    external_cmd = rr.Group(
        rr.Sequence(
            rr.MultipleChoice(0, "any",
                rr.NonTerminal("PATH"),
                rr.NonTerminal("ARG"),
            ),
            rr.NonTerminal("EOL")
        ),
        "external_cmd"
    )

    ########################################################################

    parser = rr.Diagram(
        rr.Start(label="Parser"),
        rr.MultipleChoice(0, "any",
            internal_cmd,
            external_cmd,
            rr.Skip(),
            rr.Comment("error")
        )
    )

    def create_diagram(self):
        generate_svg(self.parser, "parser")

########################################################################

def generate_svg(diagram, name):
    with open('%s.svg' % name, 'w') as foutput_svg:
        diagram.writeSvg(foutput_svg.write)

########################################################################

if __name__ == "__main__":
    main()
