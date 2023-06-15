/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_utils_bis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbechon <nbechon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:28:39 by nassm             #+#    #+#             */
/*   Updated: 2023/06/15 14:48:40 by nbechon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	The function is responsible for executing a child process with the
	specified command and I/O redirections.

	*It takes three parameters: exp_tok (the expanded token structure),
	abs_cmd_path (the absolute path to the command to be executed),
	and status (the exit status of the child process).
    
	*It checks if the input file descriptor (exp_tok->in) is different from
	the standard input file descriptor (STDIN_FILENO).
	If so, it duplicates the input file descriptor to the standard input
	file descriptor using dup2. If the duplication fails, it returns an error.
    
	*It checks if the output file descriptor (exp_tok->out) is different
	from the standard output file descriptor (STDOUT_FILENO).
        
		-It first duplicates the standard output file descriptor and stores it
		in s. If the duplication fails, it returns an error.
        
		-Then, it duplicates the output file descriptor to the standard output
		file descriptor using dup2.
		If the duplication fails, it returns an error.
    
	*It attempts to execute the command specified by abs_cmd_path with the
	arguments stored in exp_tok->cmd and the environment variables in
	get_envar()->env_var using execve.
	If execve returns, it means an error occurred, and it prints
	the error message using perror.
    
	*If the input file descriptor was changed, it closes it and duplicates the
	standard input file descriptor back to it using dup2.
    
	*If the output file descriptor was changed, it duplicates s
	(the saved standard output file descriptor) back to the standard output
	file descriptor using dup2, and then closes s.
    
	*It exits the child process with the specified status.
    
	*It returns the status value, although this line is never reached
	since the process exits before reaching it.
*/

int	execute_child(t_exp_tok *exp_tok, char *abs_cmd_path, int status)
{
	int		s;

	if (exp_tok->in != STDIN_FILENO && dup2(exp_tok->in, STDIN_FILENO) == -1)
		return (ft_perror(EXIT_FAILURE, "dup2 error"));
	if (exp_tok->out != STDOUT_FILENO)
	{
		s = dup(STDOUT_FILENO);
		if (s == -1 || dup2(exp_tok->out, STDOUT_FILENO) == -1)
			return (ft_perror(EXIT_FAILURE, "dup error"));
	}
	status = execve(abs_cmd_path, exp_tok->cmd, get_envar()->env_var);
	perror(NULL);
	if (exp_tok->in != STDIN_FILENO)
	{
		close(exp_tok->in);
		dup2(0, exp_tok->in);
	}
	if (exp_tok->out != STDOUT_FILENO)
	{
		dup2(s, STDOUT_FILENO);
		close(s);
	}
	exit(status);
	return (status);
}

int	execute_builtin(t_exp_tok *exp_tok)
{
	if (ft_strcmp(exp_tok->cmd[0], "echo") == 0)
		return (commande_echo(exp_tok->cmd));
	if (ft_strcmp(exp_tok->cmd[0], "export") == 0)
		return (commande_export(exp_tok->cmd));
	if (ft_strcmp(exp_tok->cmd[0], "env") == 0)
		return (commande_env(exp_tok->cmd));
	if (ft_strcmp(exp_tok->cmd[0], "cd") == 0)
		return (commande_cd(exp_tok->cmd));
	if (ft_strcmp(exp_tok->cmd[0], "pwd") == 0)
		return (commande_pwd(exp_tok->cmd));
	if (ft_strcmp(exp_tok->cmd[0], "unset") == 0)
		return (commande_unset(exp_tok->cmd));
	if (ft_strcmp(exp_tok->cmd[0], "exit") == 0)
		return (commande_exit(exp_tok->cmd));
	return (EXIT_FAILURE);
}

/*
	The function is responsible for executing a built-in command in a child
	process.

	*It takes a single parameter, exp_tok, which represents the expanded token
	structure containing information about the built-in command to be executed.
    
	*It declares two variables: pid to store the process ID of the child process and
	exit_status to store the exit status of the child process.
    
	*It calls fork to create a new process. If fork returns -1, it means an error
	occurred, so it returns EXIT_FAILURE.
    
	*If fork returns 0, it means the current process is the child process.
        
		-The child process calls the execute_builtin function to execute the built-in
		command specified in exp_tok.
        
		-It stores the exit status returned by execute_builtin in exit_status.
        
		-The child process then calls exit with the exit_status to terminate itself.
        
		-Note that the return (exit_status); line after exit is never
		reached since the process exits beforehand.
    
	*If the current process is the parent process (the process ID is not 0),
	it waits for the child process to finish using waitpid.
	The exit status of the child process is stored in exit_status.
    
	*Finally, the parent process returns the exit_status, which represents
	the exit status of the child process after executing the built-in command.
*/

int	execute_builtin_child(t_exp_tok *exp_tok)
{
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		exit_status = execute_builtin(exp_tok);
		exit(exit_status);
		return (exit_status);
	}
	waitpid(pid, &exit_status, 0);
	return (exit_status);
}

/*
	The function is responsible for resetting the file descriptors of a command's
	input and output to their original values after executing
	a built-in command within a pipeline.

	*It takes two parameters: exp_tok, which represents the expanded token
	structure containing information about the command, and pipes_save,
	an array storing the original file descriptors of the command's input
	and output.
    
	*If the command's input file descriptor (exp_tok->in) is different from
	the standard input file descriptor (STDIN_FILENO), it means the input
	was redirected. In this case:
        
		-It uses dup2 to restore the original input file descriptor by
		duplicating pipes_save[STDIN_FILENO] onto STDIN_FILENO.
        
		-It then closes pipes_save[STDIN_FILENO] since it's no longer needed.
    
	*If the command's output file descriptor (exp_tok->out) is different from the
	standard output file descriptor (STDOUT_FILENO), it means the output was
	redirected.
	In this case:
        
		-It uses dup2 to restore the original output file descriptor by duplicating
		pipes_save[STDOUT_FILENO] onto STDOUT_FILENO.
        
		-It then closes pipes_save[STDOUT_FILENO] since it's no longer needed.
    
	*Finally, the function returns EXIT_SUCCESS to indicate that the file
	descriptors have been successfully reset.
*/

int	exbuiltin_reset_fd(t_exp_tok *exp_tok, int pipes_save[2])
{
	if (exp_tok->in != STDIN_FILENO)
	{
		dup2(pipes_save[STDIN_FILENO], STDIN_FILENO);
		close(pipes_save[STDIN_FILENO]);
	}
	if (exp_tok->out != STDOUT_FILENO)
	{
		dup2(pipes_save[STDOUT_FILENO], STDOUT_FILENO);
		close(pipes_save[STDOUT_FILENO]);
	}
	return (EXIT_SUCCESS);
}
