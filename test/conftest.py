import sys
import pytest
import pexpect



def _expect_shell_safe(expect_func):

    def check_if_error_occured(*args, **kwargs):

        index = expect_func(*args, **kwargs)

        try:
            expect_func('yyerror')
        except pexpect.exceptions.TIMEOUT:  # No error found
            # print("%d>No error" % index)
            pass
        except pexpect.exceptions.EOF:  # Reach End Of File...
            # print("Bypassed EOF exception while looking for it...")
            pass
        else:  # yyerror Found!
            raise ExceptionShell('yyerror occured!')

        return index

    return check_if_error_occured


class ExceptionShell(Exception):
    def __init__(self, value):
        self.value = value

    def __str__(self):
        return str(self.value)


@pytest.fixture(scope="function")
def test_shell():
    proc = pexpect.spawn("../shell", encoding='utf-8', timeout=1)
    # proc.expect = _expect_shell_safe(proc.expect)

    print("| Shell PID=%d\n" % proc.pid, end="")

    return proc