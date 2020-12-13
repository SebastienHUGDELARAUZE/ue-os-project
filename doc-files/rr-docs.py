# https://github.com/tabatkins/railroad-diagrams/blob/gh-pages/README-py.md

import sys, os
import railroad as rr

########################################################################

def main():
    Parser().create_diagram()

########################################################################
# PARSER                                                               #
########################################################################

class Parser:
    echo_cmd = rr.Sequence(
        "echo",
        rr.Choice(1,
            rr.NonTerminal("{path}"),
            rr.NonTerminal("{string}"),
            rr.Comment("{command}")
        )
    )

    pwd_cmd = rr.Terminal("pwd")

    showpath_cmd = rr.Terminal("showpath")

    addpath_cmd = rr.Sequence(
        "addpath",
        rr.NonTerminal("{path}"),
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
                rr.NonTerminal("{path}"),
                rr.NonTerminal("{arg}"),
            ),
            # rr.Terminal("<<EOL>>")
        ),
        "external_cmd"
    )

    ########################################################################

    variables = rr.Group(
        rr.Choice(0,
            rr.Sequence(
                rr.NonTerminal("{id}"),
                rr.Terminal("="),
                rr.Choice(0,
                    rr.NonTerminal("{word}"),
                    rr.NonTerminal("{string}"),
                )
            ),
            rr.Sequence(
                "$",
                rr.NonTerminal("{id}"),
            )
        ),
        "variables"
    )

    ########################################################################

    handlers = rr.Group(
        rr.Sequence(
            rr.Choice(0,
                rr.Sequence(">", rr.NonTerminal("{path}")),
                rr.Sequence(">>", rr.NonTerminal("{path}")),
                rr.Sequence("|", rr.NonTerminal("[CMD]")),
                rr.Sequence("&"),
            )
        ),
        "handlers_cmd"
    )

    ########################################################################

    cmd = rr.Group(
        rr.Choice(1,
            rr.NonTerminal("[variables]"),
            rr.NonTerminal("[internal_cmd]"),
            rr.NonTerminal("[external_cmd]"),
        ),
        "CMD"
    )

    shell = rr.Sequence(
        cmd,
        handlers,
    )
        
    ########################################################################

    parser_SHELL = rr.Diagram(
        rr.Start(label="Parser"),
        rr.Choice(0,
            shell,
            rr.Comment("ERROR"),
        )
    )

    parser_VAR = rr.Diagram(
        rr.Start(type="complex", label="variables"),
        variables,
        rr.End(type="complex")
    )

    parser_INT_CMD = rr.Diagram(
        rr.Start(type="complex", label="internal_cmd"),
        internal_cmd,
        rr.End(type="complex")
    )

    parser_EXT_CMD = rr.Diagram(
        rr.Start(type="complex", label="external_cmd"),
        external_cmd,
        rr.End(type="complex")
    )

    def create_diagram(self):
        generate_svg(self.parser_SHELL, "parser-SHELL")
        generate_svg(self.parser_VAR, "parser-VAR")
        generate_svg(self.parser_INT_CMD, "parser-INT-CMD")
        generate_svg(self.parser_EXT_CMD, "parser-EXT-CMD")

########################################################################

def generate_svg(diagram, name):
    print("Generating %s..." % name, end='')
    with open('img/%s.svg' % name, 'w') as foutput_svg:
        diagram.writeSvg(foutput_svg.write)
    print("DONE")

########################################################################

if __name__ == "__main__":
    main()
