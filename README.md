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
`test/run.sh` executes all files found in the `test_cases` folder and compares the output of minishell to the one of bash.
Use `run.sh a` or `run.sh b` to also execute the test in `test_cases/bonus`

Test cases are formatted like `test_name	command to execute` (that is tab in there).

`test/test_ast.sh` is used to test the parsing into an abstract syntax tree without executing anything.
