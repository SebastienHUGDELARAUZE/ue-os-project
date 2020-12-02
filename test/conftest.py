import sys
import pytest
import pexpect

@pytest.fixture(scope="function")
def test_shell():
    child = pexpect.spawn("./main", encoding='utf-8', timeout=1)
    # child.logfile_read = sys.stdout
    return child