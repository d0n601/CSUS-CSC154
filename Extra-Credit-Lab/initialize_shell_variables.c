void
initialize_shell_variables (env, privmode)
     char **env;
     int privmode;
{
  char *name, *string, *temp_string;
  int c, char_index, string_index, string_length;
  SHELL_VAR *temp_var;

  create_variable_tables ();

  for (string_index = 0; string = env[string_index++]; )
    {

      char_index = 0;
      name = string;
      while ((c = *string++) && c != '=')
	;
      if (string[-1] == '=')
	char_index = string - name - 1;

      /* If there are weird things in the environment, like `=xxx' or a
	 string without an `=', just skip them. */
      if (char_index == 0)
	continue;

      /* ASSERT(name[char_index] == '=') */
      name[char_index] = '\0';
      /* Now, name = env variable name, string = env variable value, and
	 char_index == strlen (name) */

      temp_var = (SHELL_VAR *)NULL;

      /* If exported function, define it now.  Don't import functions from
	 the environment in privileged mode. */
      if (privmode == 0 && read_but_dont_execute == 0 && STREQN ("() {", string, 4))
	{
	  string_length = strlen (string);
	  temp_string = (char *)xmalloc (3 + string_length + char_index);

	  strcpy (temp_string, name);
	  temp_string[char_index] = ' ';
	  strcpy (temp_string + char_index + 1, string);

	  parse_and_execute (temp_string, name, SEVAL_NONINT|SEVAL_NOHIST);

	  /* Ancient backwards compatibility.  Old versions of bash exported
	     functions like name()=() {...} */
	  if (name[char_index - 1] == ')' && name[char_index - 2] == '(')
	    name[char_index - 2] = '\0';

	  if (temp_var = find_function (name))
	    {
	      VSETATTR (temp_var, (att_exported|att_imported));
	      array_needs_making = 1;
	    }
	  else
	    report_error (_("error importing function definition for `%s'"), name);

	  /* ( */
	  if (name[char_index - 1] == ')' && name[char_index - 2] == '\0')
	    name[char_index - 2] = '(';		/* ) */
	}