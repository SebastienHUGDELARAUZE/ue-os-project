VENV_NAME=venv
PYTHON=../${VENV_NAME}/bin/python

SHELL_PATH=../shell

.PHONY: run_all_test run_unit_test run_funtional_test

${SHELL_PATH}:
	$(error Shell is not present in the root directory!)

run_all_test: ${SHELL_PATH}
	${PYTHON} -m pytest . -vs

run_unit_test: ${SHELL_PATH}
	${PYTHON} -m pytest . -vs -m unit_test

run_funtional_test: ${SHELL_PATH}
	${PYTHON} -m pytest . -vs -m functional_test