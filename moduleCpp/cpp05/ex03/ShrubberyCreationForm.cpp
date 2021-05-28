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

const char *ShrubberyCreationForm::TargetFileOpenException::what() const throw()
{
    return ("Error: Failed to open file.");
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
    Form::execute(executor);
    std::ofstream	outfile;
    std::string		title;
    
    title = this->_target + std::string("_shrubbery");
    outfile.open(title);
    if (!outfile.is_open() || outfile.bad())
		throw (ShrubberyCreationForm::TargetFileOpenException());
    outfile << "                                        ////(,.###%(                             \n";       
    outfile << "                     .,.  ,****        /////*///(((((%%%%.                       \n";           
    outfile << "                 ,*,**/*/(//*(((/ *(##  ///(((###(((#%%%&&                       \n";           
    outfile << "                */((((((((##(((((((###(  */(((#(#%%%%%&&&(  (####*               \n";           
    outfile << "             (#((((#################%      *##%%##(##%&&##*.########/            \n";           
    outfile << "              . (###%%(//((#%%%&%%%%%%.   .(((&((//(&#%(((///(#####%%            \n";           
    outfile << "     ., ,,****/(#//////(((###%%%&# ,*///(#(/**,*//(((###(/#((((####%&&           \n";           
    outfile << "  ((******///(((#/((((((##%%%%%&&&&*/////(////////(((##/##########%%%%#          \n";           
    outfile << " %((((((((((((#/((((##%%%%%%%&&&&%*/**/#(#(((((((((((#%%%%%&%%%%%%%%&&&&         \n";           
    outfile << " #(  %((#(((######%%%%%%%%%&&&#((##((#####((((#######%%%%%%%%%&&&&&&&&&&&        \n";           
    outfile << "        %%%%(%%%#%%%%#%%((((((%%%%%%%%%% %####%%%%%%%%%%#(##&#%&&, #*&&          \n";           
    outfile << "     .**//((((########((((###(((/#%%%%%%%%&&&%%%%##%%###%%%#%#&&.                \n";           
    outfile << "    ,*/(((###### (#%#(((#///(((####%%#%%%%&&&%&#(((/(/(((&&%%%&&    /(           \n";           
    outfile << "    ,((((####%  .,,,##(#/((####%#%%%%%%%%%%%%#####(((((#######&&%%&&&&&.&%(      \n";           
    outfile << "    ###/ . #%#*****@@@@(/((###(##%%%@@@@@%%%%%%%%%%%%%%%####%%%%&&&&&&&&&&&&#    \n";           
    outfile << "          #((/(///&@@&&&(((((((#%&&&(&&@@@@@@&%%%%%%%%%%&&%%%%%%&&&&&&&&&&&&&&   \n";           
    outfile << "         #%##.##(((((#%%#%%%%%#&&&&&%(%&&%&&&%%%(%%&&%, &&&&&&&&&&&&&&&&,*  *,   \n";           
    outfile << "                 #%%%%%%%%%%%%(/      (   ((% (%(((/      #&&& /,% *%&(          \n";           
    outfile << "                       .% . /(%((.     (#..((%%(((.     #(*  .                   \n";           
    outfile << "                          ,%%%(%%#(*     (%(#((/(     ((*                        \n";           
    outfile << "                             ,%%(%%(((#%%%#((#(   /%((.                          \n";           
    outfile << "                                /%(%%(((%(((%###((#.                             \n";           
    outfile << "                                  *%(%%((((%((#/                                 \n";           
    outfile << "                                   .%(%#(((%#(                                   \n";           
    outfile << "                                    ##%%((%%#(                                   \n";           
    outfile << "                                    ,%%%(%%%#(*                                  \n";           
    outfile << "                                     %%((#%##(.                                  \n";           
    outfile << "                                     %%#(%%#((                                   \n";           
    outfile << "                                     (#%(%%%((                                   \n";           
    outfile << "                                     %%%#(##((                                   \n";           
    outfile << "                                    *%#%#%%(#%                                   \n";           
    outfile << "                              .*//*,******(/((*,**                               \n";           
    outfile << "                                 ,##(#(.,((#((                                   \n";
    outfile.close();
	return ;
}
