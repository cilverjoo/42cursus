// ac --> 입력받은 숫자의 갯수로 들고다닐 것.
// av --> atoi로 변환해서 int 배열에 넣어줄 것.
// 끝에는 반드시 개행이 들어가야 한다.
// stack을 입력받으면 stack a를 정렬하고 stackB를 비우기 위해서 수행해야 하는 명령어들을 개행과 함께 쭉 입력한다.
// test? ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l

#include "../../includes/push_swap.h"

int			main(int ac, char **av)
{
	t_ps	ps;
	char	*instruction;
	t_list	*new;
	t_list	*head;

	if (ac > 1)
	{
		head = ps.instr;
		ps.len = ac;
		init_stack(&ps);
		make_stack_list(av, &ps);
		read_instruction(&ps);
		execute_instr(&ps);
		check_is_ok(&ps);
	}
	return (0);
}