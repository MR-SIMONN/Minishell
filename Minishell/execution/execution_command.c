#include "../Minishell.h"



int	execution(t_env *env,t_cmd *cmds, t_data *d)
{
	d =NULL;
	
	if(is_builtin(cmds->cmd) == 0 && cmds->pipe == 0)
	{
		// apply_redirection();
		if(!execute_builtin(cmds->cmd, env, cmds->args))
			return (1);
		
	}
	// if (!ft_strcmp(cmds->cmd, "export"))
	// 	export_v(env, cmds->args);
	return (0);
}