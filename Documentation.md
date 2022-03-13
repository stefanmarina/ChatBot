Documentation


For our application GUI we used an external library called wxWidgets. You can find more about this on their official website: https://www.wxwidgets.org/

The description of the functionalities is as follows:

- Paragraph class
	- used to simplify working with paragraphs
	- contains different characteristics of a paragraphs

- countWordInText
	- counts the appearances of a word in a text
	- uses two parameters:
		- string text : the text in which the words are searched
		- string word : the string containing the words
	- implements the idea of a stemming algorithm
	- returns a score representing the number of matches in a text	

- splitTextIntoParagraphs
	- it splits a text into paragraphs
	- uses four parameters:
		- string text: the text to split into paragraphs
		- string file: the file in which we search (for later use)
		- Paragraph paragraphs[]: a Paragraph array
		- int &n : the variable which will return the length of the array

- scoreParagraphs
	- it attributes a score to each paragraph representing the number of matches
	- uses three parameters:
		- Paragraph paragraphs[] : the paragraph array
		- int n : length of the array
		- vector<string> words : words array
	- modifies the score attribute of each paragraph	
	- sorts the paragraph array based on each paragraph's score

- showParagraphs
	- shows the paragraphs
	- uses two parameters:
		- Paragraph paragraphs[] : paragraph array
		- int n : length of array

- findLearningSources
	- shows the available learning sources

- openFile
	- opens the selected learning source
	- uses one parameter:
		- string input : the name of the source

- searchFor
	- searches for the words
	- uses one parameter:
		- string input : the words to be searches

- feelingLucky
	- returns a random paragraph
