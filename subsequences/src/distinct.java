import java.util.Scanner;

public class distinct {

	public static void main(String[] args) {
		String sentence, word;
		int count = 0, i = 0, j = 0, k = 0, first = 0;
		Scanner kb = new Scanner(System.in);
		System.out.println("enter sentence");
		sentence = kb.next();
		System.out.println("enter word");
		word = kb.next();    
		int[][] key = new int[word.length() + 1][sentence.length() + 1];   //make array
		for (i = 0; i < word.length()+1; i++) {
			if (i == 0) {
				for (j = 0; j < sentence.length() + 1; j++) {   //first line is 1
					key[i][j] = 1;
				}
				continue;
			} else {
				for (j = 0; j < sentence.length() + 1; j++) {    
					if (j == 0)               //fisrt is 0
						key[i][j] = 0;
					else {
						if (word.charAt(i - 1) == sentence.charAt(j - 1) && first == 0) { 
							key[i][j] = key[i - 1][j - 1];
							first = 1;
						} else if (word.charAt(i - 1) == sentence.charAt(j - 1) && first == 1) {
							if (key[i - 1][j - 1] > key[i][j - 1])
								key[i][j] = key[i - 1][j - 1] + 1;
							else
								key[i][j] = key[i][j - 1] + 1;
						} else
							key[i][j] = key[i][j - 1];
					}
				}
			}
			first=0;
		}
		for (i = 0; i < word.length()+1; i++) {
			for (j = 0; j < sentence.length()+1; j++)
				System.out.print(key[i][j] + " ");
			System.out.println("");
		}
		System.out.println(key[word.length()][sentence.length()]);
	}
}
