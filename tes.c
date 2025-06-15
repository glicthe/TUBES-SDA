#include <stdio.h>
#include <string.h>

// Dummy implementations for demonstration
void setColorYellow() { /* Set color to yellow */ }
void setColorLightBlue() { /* Set color to light blue */ }
void setColorRed() { /* Set color to red */ }
void gotoxy(int x, int y) { /* Move cursor to (x, y) */ }
const char* cardType(int temp) {
	// Dummy: return "Draw", "Insight", or "PowerSlash" for testing
	return "Draw";
}
int temp = 0;

int main() {
	int startCol = 0, startRow = 0, i = 0;

	if (strcmp(cardType(temp), "Draw") == 0) {
		setColorYellow();
		gotoxy(startCol + 3, startRow + i); i++;
		printf("  .-<<<-.\n");
		gotoxy(startCol + 3, startRow + i); i++;
		printf(" /       \\\n");
		gotoxy(startCol + 3, startRow + i); i++;
		printf(" \\       /\n");
		gotoxy(startCol + 3, startRow + i); i++; i++;
		printf("  `->>>-`\n");
	} else if (strcmp(cardType(temp), "Insight") == 0) {
		setColorLightBlue();
		gotoxy(startCol + 5, startRow + i); i++;
		printf("\\  |  /\n");
		gotoxy(startCol + 5, startRow + i); i++;
		printf(" '.'.'\n");
		gotoxy(startCol + 5, startRow + i); i++;
		printf("~`(O)`~\n");
		gotoxy(startCol + 5, startRow + i); i++; i++;
		printf(" `-~-`\n");
	} else if (strcmp(cardType(temp), "PowerSlash") == 0) {
		setColorRed();
		gotoxy(startCol + 5, startRow + i); i++;
		printf("   /\\\n");
		gotoxy(startCol + 5, startRow + i); i++;
		printf("   ||\n");
		gotoxy(startCol + 5, startRow + i); i++;
		printf("   ||\n");
		gotoxy(startCol + 5, startRow + i); i++;
		printf(".-_||_-.\n");
		gotoxy(startCol + 5, startRow + i); i++;
		printf("   II\n");
		gotoxy(startCol + 5, startRow + i); i++; i++;
		printf("   II\n");
	}

	// Sisa print tanpa kondisi
	printf("\\  |  /\n");
	printf(" '.'.'\n");
	printf("~`(O)`~\n");
	printf(" `-~-`\n");

	printf("   /\\\n");
	printf("   ||\n");
	printf("   ||\n");
	printf(".-_||_-.\n");
	printf("   II\n");
	printf("   II\n");
	printf("     /+\\\n");
	printf("   _/_|_\\_\n");
	printf(" _/_\\_|_/_\\_\n");
	printf("/_\\_\\_|_/_/_\\\n");

	printf("     _++_   \n");
	printf("   _/|\\/|\\_\n");
	printf(" _/_\\_||_/_\\_\n");
	printf("|_|_|_||_|_/_|\n");

printf("   ^\n");
printf("   |\n");
printf("._)*(_.\n");
printf("  `I`\n");

printf("   ^\n");
printf("   |\n");
printf("._<O>_.\n");
printf("   I\n");

	printf("   .x+=:.                                .          ..    .x+=:.     ..  \n");
	printf("  z`    ^%%                              @88>  x .d88\"    z`    ^%%   888B.\n");
	printf("     .   <k  .d``                u.     %%8P    5888R        .   <k 48888E\n");
	printf("   .@8Ned8\"  @8Ne.   .u    ...ue888b     .     '888R      .@8Ned8\" '8888'\n");
	printf(" .@^%%8888\"   %%8888:u@88N   888R Y888r  .@88u    888R    .@^%%8888\"   Y88F \n");
	printf("x88:  `)8b.   `888I  888.  888R I888> ''888E`   888R   x88:  `)8b.  '88  \n");
	printf("8888N=*8888    888I  888I  888R I888>   888E    888R   8888N=*8888   8F  \n");
	printf(" %%8\"    R88    888I  888I  888R I888>   888E    888R    %%8\"    R88   4   \n");
	printf("  @8Wou 9%%   uW888L  888' u8888cJ888    888E    888R     @8Wou 9%%    .   \n");
	printf(".888888P`   '*88888Nu88P   \"*888*P\"     888&   .888B . .888888P`    u8N. \n");
	printf("`   ^\"F     ~ '88888F`       'Y\"        R888\"  ^*888%%  `   ^\"F     \"*88%% \n");
	printf("               888 ^                     \"\"      \"%%                  \"\"  \n");
	printf("               *8E                                                       \n");
	printf("               '8>                                                       \n");
	printf("                \"                                                        \n");


		printf("\n");
		printf("   _            .                   s                                            ..  \n");
		printf("  u            @88>                :8                               ..          888B.\n");
		printf(" 88Nu.   u.    %%8P                .88           u.      .u    .    @L          48888E\n");
		printf("'88888.o888c    .          .     :888ooo  ...ue888b   .d88B :@8c  9888i   .dL  '8888'\n");
		printf(" ^8888  8888  .@88u   .udR88N  -*8888888  888R Y888r =\"8888f8888r `Y888k:*888.  Y88F \n");
		printf("  8888  8888 ''888E` <888'888k   8888     888R I888>   4888>'88\"    888E  888I  '88  \n");
		printf("  8888  8888   888E  9888 'Y\"    8888     888R I888>   4888> '      888E  888I   8F  \n");
		printf("  8888  8888   888E  9888        8888     888R I888>   4888>        888E  888I   4   \n");
		printf(" .8888b.888P   888E  9888       .8888Lu= u8888cJ888   .d888L .+     888E  888I   .   \n");
		printf("  ^Y8888*\"\"    888&  ?8888u../  ^%%888*    \"*888*P\"    ^\"8888*\"     x888N><888'  u8N. \n");
		printf("    `Y\"        R888\"  \"8888P'     'Y\"       'Y\"          \"Y\"        \"88\"  888  \"*88%% \n");
		printf("                \"\"      \"P'                                               88F    \"\"  \n");
		printf("                                                                         98\"         \n");
		printf("                                                                       ./\"           \n");
		printf("                                                                      ~`             \n");
		printf("\n");
		printf("                        /\\\n");
		printf(" __                     \\/                     __\n");
		printf("(_____________________/\\/\\/\\_____________________)\n");
		printf("\n");
		printf(" _____________________      _____________________\n");
		printf("(__                   \\/\\/\\/                   __)\n");
		printf("                        /\\\n");
		printf("                        \\/\n");

		

		printf(" .--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--.\n");
		printf("/ .. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\\n");
		printf("\\ \\/\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ \\/ /\n");
		printf(" \\/ /`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\\/ / \n");
		printf(" / /\\      _            .                   s                                            ..      / /\\ \n");
		printf("/ /\\ \\    u            @88>                :8                               ..          888B.   / /\\ \\\n");
		printf("\\ \\/ /   88Nu.   u.    %%8P                .88           u.      .u    .    @L          48888E   \\ \\/ /\n");
		printf(" \\/ /   '88888.o888c    .          .     :888ooo  ...ue888b   .d88B :@8c  9888i   .dL  '8888'    \\/ / \n");
		printf(" / /\\    ^8888  8888  .@88u   .udR88N  -*8888888  888R Y888r =\"8888f8888r `Y888k:*888.  Y88F     / /\\ \n");
		printf("/ /\\ \\    8888  8888 ''888E` <888'888k   8888     888R I888>   4888>'88\"    888E  888I  '88     / /\\ \\\n");
		printf("\\ \\/ /    8888  8888   888E  9888 'Y\"    8888     888R I888>   4888> '      888E  888I   8F     \\ \\/ /\n");
		printf(" \\/ /     8888  8888   888E  9888        8888     888R I888>   4888>        888E  888I   4       \\/ / \n");
		printf(" / /\\    .8888b.888P   888E  9888       .8888Lu= u8888cJ888   .d888L .+     888E  888I   .       / /\\ \n");
		printf("/ /\\ \\    ^Y8888*\"\"    888&  ?8888u../  ^%%888*    \"*888*P\"    ^\"8888*\"     x888N><888'  u8N.    / /\\ \\\n");
		printf("\\ \\/ /      `Y\"        R888\"  \"8888P'     'Y\"       'Y\"          \"Y\"        \"88\"  888  \"*88%%    \\ \\/ /\n");
		printf(" \\/ /                   \"\"      \"P'                                               88F    \"\"      \\/ / \n");
		printf(" / /\\                                                                            98\"             / /\\ \n");
		printf("/ /\\ \\                                                                         ./\"              / /\\ \\\n");
		printf("\\ \\/ /                                                                        ~`                \\ \\/ /\n");
		printf(" / /\\.--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--.\\/ /\\ \n");
		printf("/ /\\ \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\ /\\ \\\n");
		printf("\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'  /\n");
		printf(" `--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'` \n");

// 		==========================================================================================
// 		printf(" __________________________________________      __________________________________________\n");
// 		printf("(__                                        \\/\\/\\/                                     __)\n");
// 		printf("                                             /\\\n");
// 		printf("                                             \\/\n");

// gotoxy(startX, startY++); printf("%s .--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--.\n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s/ .. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\\n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s\\ \\/\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ \\/ /\n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s \\/ /`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\\/ / \n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s / /\\%s      _            .                   s                                            ..      %s/ /\\ \n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s/ /\\ \\%s    u            @88>                :8                               ..          888B.   %s/ /\\ \\\n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s\\ \\/ /%s   88Nu.   u.    %%8P                .88           u.      .u    .    @L          48888E   %s\\ \\/ /\n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s \\/ /%s   '88888.o888c    .          .     :888ooo  ...ue888b   .d88B :@8c  9888i   .dL  '8888'    %s\\/ / \n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s / /\\%s    ^8888  8888  .@88u   .udR88N  -*8888888  888R Y888r =\"8888f8888r `Y888k:*888.  Y88F     %s/ /\\ \n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s/ /\\ \\%s    8888  8888 ''888E` <888'888k   8888     888R I888>   4888>'88\"    888E  888I  '88     %s/ /\\ \\\n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s\\ \\/ /%s    8888  8888   888E  9888 'Y\"    8888     888R I888>   4888> '      888E  888I   8F     %s\\ \\/ /\n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s \\/ /%s     8888  8888   888E  9888        8888     888R I888>   4888>        888E  888I   4       %s\\/ / \n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s / /\\%s    .8888b.888P   888E  9888       .8888Lu= u8888cJ888   .d888L .+     888E  888I   .       %s/ /\\ \n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s/ /\\ \\%s    ^Y8888*\"\"    888&  ?8888u../  ^%%888*    \"*888*P\"    ^\"8888*\"     x888N><888'  u8N.    %s/ /\\ \\\n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s\\ \\/ /%s      `Y\"        R888\"  \"8888P'     'Y\"       'Y\"          \"Y\"        \"88\"  888  \"*88%%    %s\\ \\/ /\n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s \\/ /%s                   \"\"      \"P'                                               88F    \"\"      %s\\/ / \n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s / /\\%s                                                                            98\"             %s/ /\\ \n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s/ /\\ \\%s                                                                         ./\"              %s/ /\\ \\\n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s\\ \\/ /%s                                                                        ~`                %s\\ \\/ /\n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s / /\\.--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--.\\/ /\\ \n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s/ /\\ \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\ /\\ \\\n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'  /\n", LWHITE, LRED, LWHITE);
// gotoxy(startX, startY++); printf("%s `--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'` \n", LWHITE, LRED, LWHITE);


// printf("  __________\n");
// printf(" /\\____;;___\\\n");
// printf(" | /         /\n");
// printf(" `. ())oo() .\n");
// printf("  |\\(%%()*^^()^\\\n");
// printf(" %%| |-%%-------|\n");
// printf("%% \\ | %%  ))   |\n");
// printf("%%  \\|%%________|\n");
// printf(" %%%%\n");


// void printVictoryBanner() {
// 	printf("                                                  /\\\n");
// 	printf(" __                                               \\/                                               __\n");
// 	printf("(_______________________________________________/\\/\\/\\_______________________________________________)\n");
// }

//                                              __________
// 											/\____;;___\
// 											| /        /
// 											`. ())oo() .
// 											  |\(%()*^^()^\
// 										 	 %| |-%-------| 
// 											% \ | %  ))   |
// 											%  \|%________|
// 											 %%

// 										  You earned 15 Gold!

//  ====================================================================================================

//                                   Choose A Card To Add To Your Deck:

// 									printf("                                       [card1] [card2] [card3]\n");
// 									printf("\n");
// 									printf(" _______________________________________________      _______________________________________________\n");
// 									printf("(__                                             \\/\\/\\/                                             __)\n");
// 									printf("                                                  /\\\n");
// 									printf("                                                  \\/\n");


		//  	   ,     _.._     ,
        //        (`._."`    `"._.')
        //         '._          _.'              /\
        //          | /`-.  .-'\ |             .'.'
        //          |(_()_\/_()_)| __         ( (
        //          ;   ,____,   ;'  `\        ) )
        //           \  /VvvV\  /    \  \.__   / /
        //         _/`'._`""`_.'      \  \  `\/ /
        //        /  ._-_`--'     .----.  \    /
        //       / _/      )     /  .------\`.|
        //      / / |    ``    _,|  (_`-'_\   \
        //     / /   \   \`""`   \\\\      \   \
        //    / / _   \  /                 /`  /`
        //   / _\/(    | |               ./  .'_
        //   | ( \  '--'  \             .'  (__)`\
		printf("        \\\\ `-------'            /________.'\n");

		printf("  .------------.\n");
		printf(".`              `.\n");
		printf("|                |\n");
		printf("|   @@    @@     |\n");
		printf("|   @@    @@     |\n");
		printf("|                |\n");
		printf("|    @@@@@       |\n");
		printf("|   @     @      |\n");
		printf("|                |\n");
		printf("|                |\n");
		printf("|                |\n");
		printf("|                |\n");
		printf("|                |\n");
		printf("\\/\\/\\/\\/V\\/\\/\\/\\/\n");

// gotoxy(startCol, startRow + i); i++;
// printf("            _.._     \n");
// gotoxy(startCol, startRow + i); i++;
// printf("     (`._.\"      \"._.')\n");
// gotoxy(startCol, startRow + i); i++;
// printf("      '._          _.'              /\\\n");
// gotoxy(startCol, startRow + i); i++;
// printf("       | /`-.  .-'\\ |             .'.'\n");
// gotoxy(startCol, startRow + i); i++;
// printf("       |(_()_\\/_()_)| __         ( (\n");
// gotoxy(startCol, startRow + i); i++;
// printf("       ;   ,____,   ;'  `\\        ) )\n");
// gotoxy(startCol, startRow + i); i++;
// printf("        \\  /VvvV\\  /    \\  \\.__   / /\n");
// gotoxy(startCol, startRow + i); i++;
// printf("      _/`'._----_.'      \\  \\  `\\/ /\n");
// gotoxy(startCol, startRow + i); i++;
// printf("     /  ._-_`--'     .----.  \\    /\n");
// gotoxy(startCol, startRow + i); i++;
// printf("    / _/      )     /  .------\\`.|  \n");
// gotoxy(startCol, startRow + i); i++;
// printf("   / / |    ``    _,|  (_`-'_\\   \\\n");
// gotoxy(startCol, startRow + i); i++;
// printf("  / /   \\   \\`\"\"`    \\\\\\\\     \\   \\\n");
// gotoxy(startCol, startRow + i); i++;
// printf(" / / _   \\  /                 /`  /`\n");
// gotoxy(startCol, startRow + i); i++;
// printf("/ _\\/(    | |               ./  .'_\n");
// gotoxy(startCol, startRow + i); i++;
// printf("| ( \\  '--'  \\             .'  (__)'\\\n");
// gotoxy(startCol, startRow + i); i++;
// printf("\\\\\\\\ `-------'            /________.''\n");

//    ^           ^
//   /(__.-----.__)\
//  (.`          `.)
// .`              `.
// ;   |\       /|   ;
// ;   |X\     /X|   :
// :   |XX\   /XX|   ;
// ;                 ;
// :  |`.       .`|  ;
// ;  |--`|`.`|`--|  `,
// :   | `.;;;.` |     ;._.--.
// `.    |.-.-.-.|         _`-`
//  `.                   _-
//    ;                .- 
// 	`.;`;`-;-`;-`;-`
gotoxy(startCol, startRow + i); i++;
printf("^           ^\n");
gotoxy(startCol, startRow + i); i++;
printf("  /(__.-----.__)\\\n");
gotoxy(startCol, startRow + i); i++;
printf(" (.`           `.) \n");
gotoxy(startCol, startRow + i); i++;
printf(".`               `.\n");
gotoxy(startCol, startRow + i); i++;
printf(";   |\\       /|   ;\n");
gotoxy(startCol, startRow + i); i++;
printf(";   |X\\     /X|   :\n");
gotoxy(startCol, startRow + i); i++;
printf(":   |XX\\   /XX|   ;\n");
gotoxy(startCol, startRow + i); i++;
printf(";                 ;\n");
gotoxy(startCol, startRow + i); i++;
printf(":  |`.       .`|  ;\n");
gotoxy(startCol, startRow + i); i++;
printf(";  |--`|`.`|`--|  `,\n");
gotoxy(startCol, startRow + i); i++;
printf(":   | `.;;;.` |     ;._.--.  \n");
gotoxy(startCol, startRow + i); i++;
printf("`.   |.-.-.-.|         _`-`\n");
gotoxy(startCol, startRow + i); i++;
printf(" `;                   _-\n");
gotoxy(startCol, startRow + i); i++;
printf("   ;                .- \n");
gotoxy(startCol, startRow + i); i++;
printf("    `.;`;`-;-`;-`;-`\n");



gotoxy(startCol, startRow + i); i++;
printf(" .--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--. \n");
gotoxy(startCol, startRow + i); i++;
printf("/ .. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\\n");
gotoxy(startCol, startRow + i); i++;
printf("\\ \\/\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ \\/ /\n");
gotoxy(startCol, startRow + i); i++;
printf(" \\/ /`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\\/ / \n");
gotoxy(startCol, startRow + i); i++;
printf(" / /\\        ..                .x+=:.                             ..     / /\\ \n");
gotoxy(startCol, startRow + i); i++;
printf("/ /\\ \\ x .d88\"                z`    ^%%                           888B.  / /\\ \\\n");
gotoxy(startCol, startRow + i); i++;
printf("\\ \\/ /  5888R          u.        .   <k               .u    .   48888E  \\ \\/ /\n");
gotoxy(startCol, startRow + i); i++;
printf(" \\/ /   '888R    ...ue888b     .@8Ned8\"      .u     .d88B :@8c  '8888'   \\/ / \n");
gotoxy(startCol, startRow + i); i++;
printf(" / /\\    888R    888R Y888r  .@^%%8888\"    ud8888.  =\"8888f8888r  Y88F    / /\\ \n");
gotoxy(startCol, startRow + i); i++;
printf("/ /\\ \\   888R    888R I888> x88:  `)8b. :888'8888.   4888>'88\"   '88    / /\\ \\\n");
gotoxy(startCol, startRow + i); i++;
printf("\\ \\/ /   888R    888R I888> 8888N=*8888 d888 '88%%\"   4888> '      8F    \\ \\/ /\n");
gotoxy(startCol, startRow + i); i++;
printf(" \\/ /    888R    888R I888>  %%8\"    R88 8888.+\"      4888>        4      \\/ / \n");
gotoxy(startCol, startRow + i); i++;
printf(" / /\\    888R   u8888cJ888    @8Wou 9%%  8888L       .d888L .+     .      / /\\ \n");
gotoxy(startCol, startRow + i); i++;
printf("/ /\\ \\  .888B .  \"*888*P\"   .888888P`   '8888c. .+  ^\"8888*\"     u8N.   / /\\ \\\n");
gotoxy(startCol, startRow + i); i++;
printf("\\ \\/ /  ^*888%%     'Y\"      `   ^\"F      \"88888%%       \"Y\"      \"*88%%   \\ \\/ /\n");
gotoxy(startCol, startRow + i); i++;
printf(" \\/ /     \"%%                               \"YP'                   \"\"     \\/ / \n");
gotoxy(startCol, startRow + i); i++;
printf(" / /\\.--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--./ /\\ \n");
gotoxy(startCol, startRow + i); i++;
printf("/ /\\ \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\/\\ \\\n");
gotoxy(startCol, startRow + i); i++;
printf("\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `' / \n");
gotoxy(startCol, startRow + i); i++;
printf(" `--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--' \n");



	gotoxy(startX, startY + i++); printf("%s .--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--. \n", LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s/ .. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\%s\n", YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s\\ \\/\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ \\/ /%s\n", LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s \\/ /`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\\/ / \n", YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s / /\\%s        ..                .x+=:.                             ..%s     %s/ /\\ %s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s/ /\\ \\%s x .d88\"                z`    ^%%                           888B.%s  %s/ /\\ \\%s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s\\ \\/ /%s  5888R          u.        .   <k               .u    .   48888E%s  %s\\ \\/ /%s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s \\/ /%s   '888R    ...ue888b     .@8Ned8\"      .u     .d88B :@8c  '8888'%s   %s\\/ / %s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s / /\\%s    888R    888R Y888r  .@^%%8888\"    ud8888.  =\"8888f8888r  Y88F%s    %s/ /\\ %s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s/ /\\ \\%s   888R    888R I888> x88:  `)8b. :888'8888.   4888>'88\"   '88%s    %s/ /\\ \\%s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s\\ \\/ /%s   888R    888R I888> 8888N=*8888 d888 '88%%\"   4888> '      8F%s    %s\\ \\/ /%s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s \\/ /%s    888R    888R I888>  %%8\"    R88 8888.+\"      4888>        4%s      %s\\/ / %s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s / /\\%s    888R   u8888cJ888    @8Wou 9%%  8888L       .d888L .+     .%s      %s/ /\\ %s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s/ /\\ \\%s  .888B .  \"*888*P\"   .888888P`   '8888c. .+  ^\"8888*\"     u8N.%s   %s/ /\\ \\%s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s\\ \\/ /%s  ^*888%%     'Y\"      `   ^\"F      \"88888%%       \"Y\"      \"*88%%%s   %s\\ \\/ /%s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s \\/ /%s     \"%%                               \"YP'                   \"\"%s     %s\\/ / %s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s / /\\.--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--./ /\\ %s",  LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s/ /\\ \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\/\\ \\\n", YELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `' /\n", LYELLOW, RESET);
	gotoxy(startX, startY + i++); printf("%s `--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--' \n", LYELLOW, RESET);




gotoxy(startCol, startRow + i); i++;


gotoxy(startCol, startRow + i); i++;
printf("   \"%%                               \"YP'                   \"\"  \n");
gotoxy(startCol, startRow + i); i++;
printf("\n");
gotoxy(startCol, startRow + i); i++;
printf(" .--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--. \n");
gotoxy(startCol, startRow + i); i++;
printf("/ .. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\\n");
gotoxy(startCol, startRow + i); i++;
printf("\\ \\/\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ \\/ /\n");
gotoxy(startCol, startRow + i); i++;
printf(" \\/ /`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\\/ / \n");
gotoxy(startCol, startRow + i); i++;
printf(" / /\\                                                                          ..         ..     / /\\ \n");
gotoxy(startCol, startRow + i); i++;
printf("/ /\\ \\                            x=~                                        dF          888B.  / /\\ \\\n");
gotoxy(startCol, startRow + i); i++;
printf("\\ \\/ /     .u    .               88x.   .e.   .e.                 .u    .   '88bu.      48888E  \\ \\/ /\n");
gotoxy(startCol, startRow + i); i++;
printf(" \\/ /    .d88B :@8c       .u    '8888X.x888:.x888        u      .d88B :@8c  '*88888bu   '8888'   \\/ / \n");
gotoxy(startCol, startRow + i); i++;
printf(" / /\\   =\"8888f8888r   ud8888.   `8888  888X '888k    us888u.  =\"8888f8888r   ^\"*8888N   Y88F    / /\\ \n");
gotoxy(startCol, startRow + i); i++;
printf("/ /\\ \\    4888>'88\"  :888'8888.   X888  888X  888X .@88 \"8888\"   4888>'88\"   beWE \"888L  '88    / /\\ \\\n");
gotoxy(startCol, startRow + i); i++;
printf("\\ \\/ /    4888> '    d888 '88%%\"   X888  888X  888X 9888  9888    4888> '     888E  888E   8F    \\ \\/ /\n");
gotoxy(startCol, startRow + i); i++;
printf(" \\/ /     4888>      8888.+\"      X888  888X  888X 9888  9888    4888>       888E  888E   4      \\/ / \n");
gotoxy(startCol, startRow + i); i++;
printf(" / /\\    .d888L .+   8888L       .X888  888X. 888~ 9888  9888   .d888L .+    888E  888F   .      / /\\ \n");
gotoxy(startCol, startRow + i); i++;
printf("/ /\\ \\   ^\"8888*\"    '8888c. .+  `%%88%%``\"*888Y\"    9888  9888   ^\"8888*\"    .888N..888   u8N.   / /\\ \\\n");
gotoxy(startCol, startRow + i); i++;
printf("\\ \\/ /      \"Y\"       \"88888%%      `~     `\"       \"888*\"\"888\"     \"Y\"       `\"888*\"\"   \"*88%%   \\ \\/ /\n");
gotoxy(startCol, startRow + i); i++;
printf(" \\/ /                   \"YP'                        ^Y\"   ^Y'                   \"\"        \"\"     \\/ / \n");
gotoxy(startCol, startRow + i); i++;
printf(" / /\\.--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--./ /\\ \n");
gotoxy(startCol, startRow + i); i++;
printf("/ /\\ \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\/\\ \\\n");
gotoxy(startCol, startRow + i); i++;
printf("\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `' /\n");
gotoxy(startCol, startRow + i); i++;
printf(" `--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--' \n");
gotoxy(startCol, startRow + i); i++;


	gotoxy(startX, startY++); printf("%s .--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--. %s\n", YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s/ .. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\%s\n", LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s\\ \\/\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ \\/ /%s\n", YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s \\/ /`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\\/ / %s\n", LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s / /\\%s                                                                          ..          .x+=:.     ..%s     %s/ /\\ %s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s/ /\\ \\%s                            x=~                                        dF           z`    ^%%   888B.%s  %s/ /\\ \\%s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s\\ \\/ /%s     .u    .               88x.   .e.   .e.                 .u    .   '88bu.           .   <k 48888E%s  %s\\ \\/ /%s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s \\/ /%s    .d88B :@8c       .u    '8888X.x888:.x888        u      .d88B :@8c  '*88888bu      .@8Ned8\" '8888'%s   %s\\/ / %s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s / /\\%s   =\"8888f8888r   ud8888.   `8888  888X '888k    us888u.  =\"8888f8888r   ^\"*8888N   .@^%%8888\"   Y88F%s    %s/ /\\ %s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s/ /\\ \\%s    4888>'88\"  :888'8888.   X888  888X  888X .@88 \"8888\"   4888>'88\"   beWE \"888L x88:  `)8b.  '88%s    %s/ /\\ \\%s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s\\ \\/ /%s    4888> '    d888 '88%%\"   X888  888X  888X 9888  9888    4888> '     888E  888E 8888N=*8888   8F%s    %s\\ \\/ /%s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s \\/ /%s     4888>      8888.+\"      X888  888X  888X 9888  9888    4888>       888E  888E  %%8\"    R88   4%s      %s\\/ / %s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s / /\\%s    .d888L .+   8888L       .X888  888X. 888~ 9888  9888   .d888L .+    888E  888F   @8Wou 9%%    .%s      %s/ /\\ %s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s/ /\\ \\%s   ^\"8888*\"    '8888c. .+  `%%88%%``\"*888Y\"    9888  9888   ^\"8888*\"    .888N..888  .888888P`    u8N.%s   %s/ /\\ \\%s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s\\ \\/ /%s      \"Y\"       \"88888%%      `~     `\"       \"888*\"\"888\"     \"Y\"       `\"888*\"\"   `   ^\"F     \"*88%%%s   %s\\ \\/ /%s\n",YELLOW, LRED, RESET, YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s \\/ /%s                   \"YP'                        ^Y\"   ^Y'                   \"\"                    \"\"%s     %s\\/ / %s\n",LYELLOW, LRED, RESET, LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s / /\\.--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--..--./ /\\ %s\n", YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s/ /\\ \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\/\\ \\%s\n", LYELLOW, RESET);
	gotoxy(startX, startY++); printf("%s\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `' /`' / %s\n", YELLOW, RESET);
	gotoxy(startX, startY++); printf("%s `--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--' %s\n", LYELLOW, RESET);

	return 0;
}
