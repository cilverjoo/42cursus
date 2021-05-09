#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : Form("Shruberry Creation", 145, 137), _target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &ref) : Form(ref), _target(ref._target)
{
}


ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm &ref)
{
    if (this == &ref)
        return (*this);
    Form::operator=(ref);
    this->_target = ref._target;
	return (*this);
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
    Form::execute(executor);
    std::ofstream out(_target + "_shrubbery");

    std::cout << "                                        ////(,.###%(                             \n";       
    std::cout << "                     .,.  ,****        /////*///(((((%%%%.                       \n";           
    std::cout << "                 ,*,**/*/(//*(((/ *(##  ///(((###(((#%%%&&                       \n";           
    std::cout << "                */((((((((##(((((((###(  */(((#(#%%%%%&&&(  (####*               \n";           
    std::cout << "             (#((((#################%      *##%%##(##%&&##*.########/            \n";           
    std::cout << "              . (###%%(//((#%%%&%%%%%%.   .(((&((//(&#%(((///(#####%%            \n";           
    std::cout << "     ., ,,****/(#//////(((###%%%&# ,*///(#(/**,*//(((###(/#((((####%&&           \n";           
    std::cout << "  ((******///(((#/((((((##%%%%%&&&&*/////(////////(((##/##########%%%%#          \n";           
    std::cout << " %((((((((((((#/((((##%%%%%%%&&&&%*/**/#(#(((((((((((#%%%%%&%%%%%%%%&&&&         \n";           
    std::cout << " #(  %((#(((######%%%%%%%%%&&&#((##((#####((((#######%%%%%%%%%&&&&&&&&&&&        \n";           
    std::cout << "        %%%%(%%%#%%%%#%%((((((%%%%%%%%%% %####%%%%%%%%%%#(##&#%&&, #*&&          \n";           
    std::cout << "     .**//((((########((((###(((/#%%%%%%%%&&&%%%%##%%###%%%#%#&&.                \n";           
    std::cout << "    ,*/(((###### (#%#(((#///(((####%%#%%%%&&&%&#(((/(/(((&&%%%&&    /(           \n";           
    std::cout << "    ,((((####%  .,,,##(#/((####%#%%%%%%%%%%%%#####(((((#######&&%%&&&&&.&%(      \n";           
    std::cout << "    ###/ . #%#*****@@@@(/((###(##%%%@@@@@%%%%%%%%%%%%%%%####%%%%&&&&&&&&&&&&#    \n";           
    std::cout << "          #((/(///&@@&&&(((((((#%&&&(&&@@@@@@&%%%%%%%%%%&&%%%%%%&&&&&&&&&&&&&&   \n";           
    std::cout << "         #%##.##(((((#%%#%%%%%#&&&&&%(%&&%&&&%%%(%%&&%, &&&&&&&&&&&&&&&&,*  *,   \n";           
    std::cout << "                 #%%%%%%%%%%%%(/      (   ((% (%(((/      #&&& /,% *%&(          \n";           
    std::cout << "                       .% . /(%((.     (#..((%%(((.     #(*  .                   \n";           
    std::cout << "                          ,%%%(%%#(*     (%(#((/(     ((*                        \n";           
    std::cout << "                             ,%%(%%(((#%%%#((#(   /%((.                          \n";           
    std::cout << "                                /%(%%(((%(((%###((#.                             \n";           
    std::cout << "                                  *%(%%((((%((#/                                 \n";           
    std::cout << "                                   .%(%#(((%#(                                   \n";           
    std::cout << "                                    ##%%((%%#(                                   \n";           
    std::cout << "                                    ,%%%(%%%#(*                                  \n";           
    std::cout << "                                     %%((#%##(.                                  \n";           
    std::cout << "                                     %%#(%%#((                                   \n";           
    std::cout << "                                     (#%(%%%((                                   \n";           
    std::cout << "                                     %%%#(##((                                   \n";           
    std::cout << "                                    *%#%#%%(#%                                   \n";           
    std::cout << "                              .*//*,******(/((*,**                               \n";           
    std::cout << "                               ,##(#(.,((#((                                     \n";           
    
}