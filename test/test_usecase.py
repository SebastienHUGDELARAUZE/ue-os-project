import pytest
import pexpect
import sys

# TO CHECK: https://docs.pytest.org/en/stable/getting-started.html#request-a-unique-temporary-directory-for-functional-tests



@pytest.mark.functional_test
class Test_Use_Case():

    @pytest.mark.skip(reason="Issue: No exception on error exit")
    def test_end_result(self, test_shell):
        test_shell.logfile_read = sys.stdout

        # PATH RELATED : FEAT-3 > EXEC-CMD > INT-CMD
        test_shell.sendline("delpath")
        test_shell.sendline("addpath /bin")
        test_shell.sendline("addpath /usr/local/bin")
        test_shell.sendline("showpath")
        test_shell.expect("/bin:/usr/local/bin")

        # VAR & CMD & REDIR RELATED
        test_shell.sendline("fichier=\"mon fichier.txt\"")
        test_shell.sendline("touch $fichier fichier2.txt")
        test_shell.sendline("ls -al $fichier")
        test_shell.sendline("ls -al > resultat.txt")
        test_shell.sendline("ls -al | grep fichier")
        test_shell.expect(["mon fichier.txt", "fichier2.txt"])
