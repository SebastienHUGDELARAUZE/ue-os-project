import pytest
import pexpect
import os
import sys

from conftest import ExceptionShell


NEW_LINE="\r\n"



@pytest.mark.unit_test
class Test_Internal_Command():

    def test_echo(self, test_shell):
        word = "test"
        path = "/test/path"
        string = "\"str ing\""

        test_shell.sendline("echo " + word)
        test_shell.expect(word)

        test_shell.sendline("echo " + path)
        test_shell.expect(path)

        test_shell.sendline("echo " + string)
        test_shell.expect(string)

    def test_pwd(self, test_shell):
        cwd = os.getcwd()
        test_shell.sendline("pwd")
        test_shell.expect("PWD=%s" % cwd)

    def test_showpath_addpath(self, test_shell):
        path = "/bin"

        test_shell.sendline("addpath " + path)
        test_shell.sendline("showpath")
        test_shell.expect("PATH=" + path + NEW_LINE)

    def test_addpath_delpath_showpath(self, test_shell):
        path = "/bin"

        test_shell.sendline("addpath " + path)
        test_shell.sendline("showpath")
        test_shell.expect("PATH=" + path + NEW_LINE)

        test_shell.sendline("delpath")

        test_shell.sendline("showpath")
        test_shell.expect("PATH=" + NEW_LINE)

    def test_var(self, test_shell):
        # test_shell.logfile_read = sys.stdout

        word="IMT"
        bad_string="IMT Atlantique"
        good_string="\"IMT Atlantique\""

        test_shell.sendline("var="+word)
        test_shell.sendline("echo $var")
        test_shell.expect(word + NEW_LINE)

        test_shell.sendline("var="+bad_string)
        test_shell.sendline("echo $var")
        test_shell.expect("No such file or directory")

        test_shell.sendline("var="+good_string)
        test_shell.sendline("echo $var")
        test_shell.expect(good_string + NEW_LINE)


@pytest.mark.unit_test
class Test_External_Command():

    def test_execute_path_without_args(self, test_shell):
        test_shell.logfile_read = sys.stdout
        
        path = "/bin/ls"

        test_shell.sendline(path)
        test_shell.sendeof()
        test_shell.read()

    def test_execute_path_with_args(self, test_shell):
        # test_shell.logfile_read = sys.stdout
        
        path = "/bin/ls -al"

        test_shell.sendline(path)
        test_shell.expect("..")

    def test_execute_cmd_with_args(self, test_shell):
        # test_shell.logfile_read = sys.stdout
        
        path = "/bin"
        cmd = "ls -al"

        test_shell.sendline("addpath " + path)
        test_shell.sendline(cmd)
        test_shell.expect("..")
