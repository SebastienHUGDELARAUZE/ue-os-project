all: shell test

##############################################################
###### Python Virtual Env

VENV_NAME?=venv
PYTHON=${VENV_NAME}/bin/python

.PHONY: prepare_venv prepare_venv_dev prepare_ci_env

prepare_ci_env:
	pip install -r test/requirements.txt

prepare_venv: ${VENV_NAME}/bin/activate

prepare_venv_dev: prepare_venv
	${PYTHON} -m pip install -r requirements.txt
	touch ${VENV_NAME}/bin/activate

${VENV_NAME}/bin/activate: test/requirements.txt
	test -d ${VENV_NAME} || python3 -m venv ${VENV_NAME}
	${PYTHON} -m pip install -r test/requirements.txt
	touch ${VENV_NAME}/bin/activate

##############################################################
###### SHELL DIR

.PHONY: shell

shell:
	(cd src/; make build_shell)

install: shell
	(cp ./src/shell .)

run_shell: install
	(./shell)

###### DOCS DIR

build_docs: prepare_venv_dev
	(cd doc-files/; make VENV_NAME=${VENV_NAME})

###### TEST DIR

test: prepare_venv install
	(cd test; make run_all_test)

unit_test: prepare_venv install
	(cd test; make run_unit_test)

func_test: prepare_venv install
	(cd test; make run_functional_test)

ci_test:
	(cd test; make run_all_test)

###### CLEAN

clean:
	(cd src/; make realclean)

realclean: clean
	rm -rf shell
