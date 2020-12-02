import pytest
import pexpect
import os
import sys

from conftest import ExceptionShell


NEW_LINE="\r\n"



@pytest.mark.unit_test
class Test_Internal_Command():

    def test_echo(self, test_shell):
        test_shell.sendline("echo test")
        test_shell.expect("test")

    def test_pwd(self, test_shell):
        cwd = os.getcwd()
        test_shell.sendline("pwd")
        test_shell.expect("PWD=%s" % cwd)

    def test_showpath(self, test_shell):
        test_shell.sendline("showpath")
        test_shell.expect("PATH="+NEW_LINE)

    def test_addpath(self, test_shell):
        test_shell.sendline("addpath /bin")
        test_shell.expect("/bin"+NEW_LINE)

    def test_delpath(self, test_shell):
        test_shell.sendline("addpath /bin")
        test_shell.expect("/bin"+NEW_LINE)

        test_shell.sendline("delpath")

        test_shell.sendline("showpath")
        test_shell.expect("PATH="+NEW_LINE)


@pytest.mark.unit_test
class Test_External_Command():

    def test_yyerror_raised(self, test_shell):
        test_shell.sendline("XXX")
        with pytest.raises(ExceptionShell):
            test_shell.expect("XXX")