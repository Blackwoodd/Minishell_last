/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nassm <nassm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:13:47 by nassm             #+#    #+#             */
/*   Updated: 2023/06/07 13:56:46 by nassm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
    The function checks if the given last_pipe_out file descriptor is
    not equal to 0 or 1, indicating that it is not a valid pipe file descriptor.

    *The function is_not_pipe takes a single parameter last_pipe_out, which
    represents the file descriptor of the last pipe output.
    
    *It first checks if last_pipe_out is not equal to 0 and not equal to 1.
    
    *If the condition is true, it enters the conditional block.
        
        -Inside the conditional block, it closes the last_pipe_out
        file descriptor using the close function.
        
        -It then writes an error message, "Error opening pipe," to
        the standard error file descriptor using ft_putstr_fd.
       
        -Finally, it returns EXIT_FAILURE to indicate that an error occurred.
    
    *If the condition is false, indicating that last_pipe_out is a valid pipe
    file descriptor, it simply returns EXIT_SUCCESS to indicate success.
*/

static int  is_not_pipe(int last_pipe_out)
{
    if (last_pipe_out != 0 && last_pipe_out != 1)
    {
        close(last_pipe_out);
        ft_putstr_fd("Errror opening pipe\n", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

/*
    The function is responsible for setting up the input
    file descriptor (in) for a command and validating the
    last pipe output file descriptor (last_pipe_out).

    *The function pipe_t_zero takes two parameters: last_pipe_out, a pointer
    to the last pipe output file descriptor, and exp_tok, a pointer to a
    structure t_exp_tok containing command execution information.
    
    *It first checks if the value of last_pipe_out is 0, indicating an
    invalid pipe file descriptor.
        
        -If the condition is true, it writes an error message, "Error, opening pipe," to
        the standard error file descriptor using ft_putstr_fd.
        
        -It then returns EXIT_FAILURE to indicate an error occurred.
    
    *If the last_pipe_out is not 0, indicating a valid pipe file descriptor, 
    t continues to the next check.
        
        -It checks if exp_tok->in is 0, indicating that the input file descriptor
        has not been set yet.
            
            -If the condition is true, it sets exp_tok->in to the value of last_pipe_out,
            indicating that the command will read input from the pipe.
            
            -If the condition is false, indicating that exp_tok->in is already set,
            it enters the else if block.
        
        -Inside the else if block, it checks if last_pipe_out is neither 0 nor 1,
        indicating an invalid pipe file descriptor.
            
            -If the condition is true, it closes the last_pipe_out file descriptor
            using the close function to release the resources.
    
    *Finally, it sets *last_pipe_out to 0, indicating that the current
    command is the first in the pipeline.
    
    *The function returns EXIT_SUCCESS to indicate success.
*/

static int  pipe_t_zero(int *last_pipe_out, t_exp_tok *exp_tok)
{
    if (*last_pipe_out == 0)
    {
        ft_putstr_fd("Error, opening pipe \n", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
    if (exp_tok->in == 0)
        exp_tok->in = *last_pipe_out;
    else if (*last_pipe_out != 0 && *last_pipe_out != 1)
        close (*last_pipe_out);
    *last_pipe_out = 0;
    return (EXIT_SUCCESS);
}

/*
    The function pipe_t_one is
    responsible for setting up the output file descriptor
    (out) for a command and creating a new pipe.
    
    *The function pipe_t_one takes two parameters: last_pipe_out, a pointer to the
    last pipe output file descriptor, and exp_tok, a pointer to a structure
    t_exp_tok containing command execution information.
    
    *Inside the function, an integer array pipes of size 2 is declared
    to store the file descriptors of the pipe.
    
    *It uses the pipe system call to create a new pipe and store the file descriptors
    in the pipes array. If the pipe call fails (returns a non-zero value),
    indicating an error, it returns ft_perror(EXIT_FAILURE, "pipe error").
    The ft_perror function is assumed to print an error message and
    exit with the specified failure status.
    
    *If the pipe call is successful, it sets *last_pipe_out to pipes[0],
    which is the read end of the pipe.
    
    *Next, it checks if exp_tok->out is 1, indicating that the
    output file descriptor has not been set yet.
        
        -If the condition is true, it sets exp_tok->out to pipes[1], which is
        the write end of the pipe, indicating that the command will
        write its output to the pipe.
        
        -If the condition is false, indicating that
        exp_tok->out is already set, it enters the else block.
    
    *Inside the else block, it closes pipes[1], the write end of the pipe,
    using the close function to release the resources.
    
    *Finally, the function returns EXIT_SUCCESS to indicate success.
*/

static int pipe_t_one(int *last_pipe_out, t_exp_tok *exp_tok)
{
    int pipes[2];

    if (pipe(pipes) != 0)
        return (ft_perror(EXIT_FAILURE, "pipe error)"));
    *last_pipe_out = pipes[0];
    if (exp_tok->out == 1)
        exp_tok->out = pipes[1];
    else
        close(pipes[1]);
    return (EXIT_SUCCESS);
}

/*
    The function is responsible for setting up both the input
    and output file descriptors for a command and creating a new pipe.

    *The function pipe_t_two takes two parameters: last_pipe_out, a pointer to the
    last pipe output file descriptor, and exp_tok, a pointer to a structure t_exp_tok
    containing command execution information.
    
    *Inside the function, an integer array pipes of size 2 is declared
    to store the file descriptors of the pipe.
    
    *It checks if *last_pipe_out is equal to 0, which indicates an error opening the pipe.
    If true, it prints an error message and returns EXIT_FAILURE.
    
    *If exp_tok->in is 0, indicating that the input file descriptor has not been set yet,
    it sets exp_tok->in to the value of *last_pipe_out.
    
    *If exp_tok->in is already set or *last_pipe_out is not 0 or 1, it
    closes *last_pipe_out to release the resources.
    
    *It sets *last_pipe_out to 0 to prepare for a new pipe.
    
    *It uses the pipe system call to create a new pipe and store the file descriptors
    in the pipes array. If the pipe call fails (returns a non-zero value),
    it returns ft_perror(EXIT_FAILURE, "pipe error").
    
    *If the pipe call is successful, it sets *last_pipe_out to pipes[0],
    which is the read end of the pipe.
    
    *Next, it checks if exp_tok->out is 1, indicating that the output
    file descriptor has not been set yet.
        
        -If the condition is true, it sets exp_tok->out to pipes[1],
        which is the write end of the pipe, indicating that the
        command will write its output to the pipe.
        
        -If the condition is false, indicating that exp_tok->out is already set,
        it enters the else block.
    
    *Inside the else block, it closes pipes[1], the write end of the pipe,
    using the close function to release the resources.
    
    *Finally, the function returns EXIT_SUCCESS to indicate success.
*/

static int pipe_t_two(int *last_pipe_out, t_exp_tok *exp_tok)
{
    int pipes[2];
    
    if (*last_pipe_out == 0)
    {
        ft_putstr_fd("Errror opening pipe\n", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
    if (exp_tok->in == 0)
        exp_tok->in = *last_pipe_out;
    else if (*last_pipe_out != 0 && *last_pipe_out != 1)
        close (*last_pipe_out);
    *last_pipe_out = 0;
    if (pipe(pipes) != 0)
        return (ft_perror(EXIT_FAILURE, "pipe error"));
    *last_pipe_out = pipes[0];
    if (exp_tok->out == 1)
        exp_tok->out = pipes[1];
    else
        close(pipes[1]);
    return (EXIT_SUCCESS);
}

/*
    The function is responsible for managing the different types of pipes
    based on the pipe_type parameter.

    *The function handle_pipes takes two parameters: exp_tok, a pointer
    to a structure t_exp_tok containing command execution information,
    and pipe_type, an integer representing the type of pipe operation.
    
    *It declares a static integer variable last_pipe_out to store
    the file descriptor of the last pipe output. The use of the
    static keyword ensures that the variable retains its value
    across multiple function calls.
    
    *The function then uses a series of conditional statements to handle
    different pipe_type values:
        
        -If pipe_type is -1, it calls the is_not_pipe function to check if
        the last_pipe_out value is valid. The function is_not_pipe is responsible
        for handling cases where the last_pipe_out value is not a valid file descriptor,
        and it returns an appropriate exit status.
        
        -If pipe_type is 0, it calls the pipe_t_zero function to handle
        the case where the pipe operation is 0. The function pipe_t_zero sets
        up the input file descriptor for the command based on
        the last_pipe_out value and returns an appropriate exit status.
        
        -If pipe_type is 1, it calls the pipe_t_one function to handle
        the case where the pipe operation is 1.
        The function pipe_t_one creates a new pipe, sets up the output
        file descriptor for the command, and returns an appropriate exit status.
        
        -If pipe_type is 2, it calls the pipe_t_two function to
        handle the case where the pipe operation is 2.
        The function pipe_t_two sets up both the input and output
        file descriptors for the command, creates a
        new pipe if necessary, and returns an appropriate exit status.
    
    *If none of the conditional statements match,
    it returns EXIT_SUCCESS to indicate successful execution.
*/

int handle_pipes(t_exp_tok *exp_tok, int pipe_type)
{
    static int  last_pipe_out;

    if (pipe_type == -1)
        return (is_not_pipe(last_pipe_out));
    else if (pipe_type == 0)
        return (pipe_t_zero(&last_pipe_out, exp_tok));
    else if (pipe_type == 1)
        return(pipe_t_one(&last_pipe_out, exp_tok));
    else if (pipe_type ==2)
        return (pipe_t_two(&last_pipe_out, exp_tok));
    return (EXIT_SUCCESS);
}