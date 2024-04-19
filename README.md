## Working
- Display a prompt
- Have a working history
- Search and launch the right executable
- Pipes
- && and || with parenthesis for priorities
- echo

## Todo-List
- Hanlde quotes (single and double) in the tokenizer
- Implement redirections (<, >, << and >>), need to extend the parser
- Handle environment variables (can resuse the code from path extraction)
- Handle $?
- Hanlde signals (ctrl-C, ctrl-D and ctrl-\) in interactive mode
- Implement builins:
	- cd with only a relative or absolute path
	- pwd with no options
    - export with no options
	- unset with no options
	- env with no options or arguments
- write automated valgrind tests for memory leaks
- better error messages on syntax errors
- bonus: wildcards `*` for current working directory

## Known Bugs
- Some syntax (missing space before or after parenthesis) is not tokenized correctly

## Tests
Tests are in the test folder. `run.sh` executes all files found in the `test_cases` folder and compares the output (stdout, stderr and return status) of minishell to the one of bash.

Usage:
- `./run.sh` to execute all tests except bonus tests
- `./run.sh a` or `./run.sh b` to also execute the tests in `test_cases/bonus`
- `./run.sh /builtins/echo` to execute only the tests in a specific file

Test cases are formatted like `test_name	command to execute; cmd 2; cmd3` (that is a tab in there). `;`s are replaced by newlines, this allows for executing multiple commands per test, even if minishell does not support `;`.

`test_ast.sh` is used to test the parsing into an abstract syntax tree without executing anything.
