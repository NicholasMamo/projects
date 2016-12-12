from collections import OrderedDict
from math import sqrt
from nltk.corpus import brown
from nltk.tokenize import word_tokenize

training_set_percentage = 10/100
training_set_size = int(len(brown.fileids()) * training_set_percentage)
most_common = ['.', 0]

#-------------------------------------------------------#
#                 GENERAL FUNCTIONS                     #
#-------------------------------------------------------#

# get the index of element in the list to check
# usage: print(index_of([['a', 'b', 'c'], ['b', 'a', 'c'], ['c', 'a', 'b']], ['a', 'b']))
def index_of(check, element):
	length = len(element) # get the length of the element
	counter = -1 # initialize the counter to -1
	for iterator in check: # go through the list
		counter += 1 # increment the counter
		if (iterator[0:length] == element): # if the first part of the iterator, with equal length to the element's length, is the same as the element
			return counter # return the index
	return -1 # if the element is not found, return -1
	
#-------------------------------------------------------#
#                LEARNING FUNCTIONS                     #
#-------------------------------------------------------#

# get the tagged sentences starting from document i, up to document i + length (exclusive)
def get_tagged_sentences(i, length, skip):
	tagged_sentences = []
	for document in range(i, i + length): # go through all documents
		if (not (document in skip)):
			document_sentences = brown.tagged_sents(brown.fileids()[document], tagset="universal") # get all the sentences in the document
			tagged_sentences += [document_sentences[i] for i in range(0, len(document_sentences))] # append the sentences to the tagged sentences
	return tagged_sentences
	
# get the tagged words starting from document i, up to document i + length (exclusive)
def get_tagged_words(i, length, skip):
	tagged_words = []
	for document in range(i, i + length): # go through all documents
		if (not (document in skip)):
			document_words = brown.tagged_words(brown.fileids()[document], tagset="universal") # get all the sentences in the document
			tagged_words += [document_words[i] for i in range(0, len(document_words))] # append the sentences to the tagged sentences
	return tagged_words

# get the most common tag starting from document i, up to document i + length (exclusive)
def get_most_common_tag(i, length, skip):
	tagged_words = get_tagged_words(i, length, skip) # get the tagged words
	tags = [tagged_words[i][1] for i in range(0, len(tagged_words))] # extract the tags from the words
	total = len(tags) # count the total number of tags
	total_tags = {} # the dictionary of total tags
	
	for tag in tags: # go through each tag
		if (total_tags.get(tag, -1) == -1): # if the tag has not been encountered yet
			total_tags[tag] = 1 / total # add the tag to the dictionary
		else: # if the tag has been defined in the dictionary
			total_tags[tag] += 1 / total # add to its probability
	
	most_common = ['.', 0] # initialize the most common tag with a default tag and probability 
	tag_keys = list(total_tags.keys()) # get the different tags
	for i in range(0, len(total_tags)): # go through all the tags
		if (total_tags.get(tag_keys[i]) > most_common[1]): # if the tag appears more than the current most common tag
			most_common[0] = tag_keys[i] # change the most common tag's name to the new one
			most_common[1] = total_tags.get(tag_keys[i]) # change the most common tag's probability to the new one
	
	return most_common

# calculate the start state probabilities of the training set
def initialize_start_probabilities(i, length, skip):
	tagged_sentences = get_tagged_sentences(i, length, skip) # get the tagged sentences
	tags = [tagged_sentences[i][0][1] for i in range (0, len(tagged_sentences))] # get all the tags of the first words in each sentence
	
	probabilities = {} # the probabilities that a tag is used to start a sentence
	total_sentences = len(tags) # calculate the total number of sentences
	for tag in tags: # visit each tag
		if (probabilities.get(tag, -1) == -1): # if the tag has not been used in the start of a sentence yet
			probabilities[tag] = 1/total_sentences # initialize it in the dictionary
		else: # if the tag has been used in the start of a sentence
			probabilities[tag] += 1/total_sentences # increment the number of times it has appeared in the start of a sentence
	
	return probabilities
	
# calculate the tag probabilities for words
def initialize_word_probabilities(i, length, skip):
	word_totals = {} # the total number of times a word appears
	words = get_tagged_words(i, length, skip) # get the tagged words
	for tagged_word in words: # visit each word
		word = tagged_word[0].lower()
		if (word_totals.get(word, -1) == -1): # if the word has not been declared in the dictionary
			word_totals[word] = 1 # initialize it in the dictionary
		else: # if the word has been declared in the dictionary
			word_totals[word] += 1 # increment the number of times it has appeared
			
	tags = [words[i][1] for i in range(0, len(words))] # extract the tags from the words
	total_tags = {} # the dictionary of total tags
	
	for tag in tags: # go through each tag
		if (total_tags.get(tag, -1) == -1): # if the tag has not been encountered yet
			total_tags[tag] = 1 # add the tag to the dictionary
		else: # if the tag has been defined in the dictionary
			total_tags[tag] += 1 # add to its probability
			
	word_tag_probabilities = [] # the probability that a word appears tagged with a particular tag
	for tagged_word in words: # visit each word
		word = tagged_word[0].lower() # get the actual word
		tag = tagged_word[1] # get the word's tag
		weight = 1 / total_tags[tag] # the weight is inversely proportional to the number of times that the tag appears
		#weight = 1 / word_totals.get(word) # the weight is inversely proportional to the number of times that the word appears
		tagged = [word, tag, weight] # create the tagged word
		
		index = index_of(word_tag_probabilities, tagged[0:2]) # look for the tagged word
		if (index == -1): # if the tagged word combination has not been declared in the dictionary
			word_tag_probabilities.append(tagged) # initialize it in the dictionary
		else: # if the tagged word combination has been declared in the dictionary
			word_tag_probabilities[index][2] += weight # increment the number of times the word has appeared with that particular tag
	
	return word_tag_probabilities
	
# calculate the tag succession probabilities - how likely it is that tag 'i' is followed by tag 'j'
def initialize_tag_probabilities(i, length, skip):
	tag_totals = OrderedDict() # the total number of times a tag combination appears
	words = get_tagged_words(i, length, skip) # get the tagged words
	for tagged_word in words: # visit each word
		tag = tagged_word[1]
		if (tag_totals.get(tag, -1) == -1): # if the word has not been declared in the dictionary
			tag_totals[tag] = 1 # initialize it in the dictionary
		else: # if the word has been declared in the dictionary
			tag_totals[tag] += 1 # increment the number of times it has appeared
			
	tag_couple_probabilities = OrderedDict() # the probability that tag 'i' is followed by tag 'j'
	tags = tag_totals.keys() # get the different tags
	for tag in tags: # go through each tag
		tag_couple_probabilities[tag] = OrderedDict() # create an empty dictionary for this tag
		for succession in tags: # go through each other tag
			tag_couple_probabilities[tag][succession] = 0 # initialize the probability that any tag is followed by any other tag to 0
			
	bigrams = [[words[i][1], words[i+1][1]] for i in range(0, len(words) -1)] # get all the tag bigrams in the documents
	for bigram in bigrams: # go through each bigram
		tag = bigram[0] # get the first part of the bigram
		succession = bigram[1] # get the second part of the bigram
		weight = 1 / tag_totals[tag] # the weight to be added is inversely proportional to the number of times that the tag appears to conserve probability between 0 and 1
		tag_couple_probabilities[tag][succession] += weight # add the weight to the probability
		
	return tag_couple_probabilities
	
#-------------------------------------------------------#
#                    USER FUNCTIONS                     #
#-------------------------------------------------------#
	
def get_input():
	print("input: ", end = "") # ask for the input
	user_input = input() # fetch the input
	return user_input.lower() # convert it to lowercase
	
#-------------------------------------------------------#
#                  VITERBI FUNCTIONS                    #
#-------------------------------------------------------#

# print the viterbi matrix
def print_matrix(matrix):
	tokens = matrix.keys() # get the different tokens
	print("\t", end="") # skip a tab where the tag column will come
	for token in tokens: # go through each token
		print(token, end = "\t\t") # print the token and leave space for the probability
	print("") # print an empty line
	
	tags = OrderedDict(list(matrix.items())[0][1]).keys() # get all the different tags from the first token
	for tag in tags: # go through each tag
		print(tag, end = "\t") # print the tag, and pad with one tab
		for token in tokens: # go through each token
			print("%.9f" % matrix[token][tag], end = "\t") # print the value of the cell with 9 decimal places
		print("") # print an empty line
	
	print("") # print an empty line

# get the maximum value in the column of the given token
def get_max(matrix, token, tags):
	max_value = ['.', 0] # initialize the maximum value to a default tag and 0
	for tag in tags: # go through each tag
		if (matrix[token][tag] > max_value[1]): # if the token-tag combination is greater than the maximum value
			max_value[0] = tag # set the maximum value to the cell value
			max_value[1] = matrix[token][tag] # set the maximum value to the cell value
	return max_value

# initialize the matrix
def initialize_matrix(tokens, tags):
	matrix = OrderedDict() # use an OrderedDict as order is important
	for token in tokens: # go through each token
		matrix[token] = OrderedDict() # create another OrderedDict for each token
		for tag in tags: # go through all the tags
			matrix[token][tag] = 0 # set the value of the cell to 0
	return matrix

# initialize the first column of the matrix, which is special because it uses the start state probabilities
def calculate_first_column(matrix, tokens, tags, start_probabilities, word_tag_probabilities):
	start_token = tokens[0] # get the first token to initialize the first column
	marked = False # a flag indicating whether the token has been matched with a possible tag or not
	for tag in tags: # go through each tag
		index = index_of(word_tag_probabilities, [start_token, tag]) # get the index of the first token and the tag
		if (index > -1): # if the token has been encountered before
			matrix[start_token][tag] = sqrt(start_probabilities.get(tag) * word_tag_probabilities[index][2]) # calculate the cell value
			marked = True # mark the token as having been matched with a possible tag
	if (not(marked)): # if no suitable tag has been found for the token - the token has never been encountered in training
		matrix[start_token][most_common[0]] = sqrt(start_probabilities.get(most_common[0]) * most_common[1]) # use the most common value to calculate the cell value
	return matrix

# calculate the columns of the matrix
def calculate_columns(matrix, tokens, tags, tag_probabilities, word_tag_probabilities):	
	for i in range(1, len(tokens)): # skip the first token, as its column was already calculated
		previous_max = get_max(matrix, tokens[i - 1], tags) # get the maximum value from the previous column
		token = tokens[i] # get the current token, whose column will be updated
		marked = False # a flag indicating whether the token has been matched with a possible tag or not
		for tag in tags: # go through each tag
			index = index_of(word_tag_probabilities, [token, tag]) # get the index of the token and the tag
			if (index > -1): # if the token has been encountered before
				matrix[token][tag] = sqrt(previous_max[1] * tag_probabilities[previous_max[0]][tag] * word_tag_probabilities[index][2]) # calculate the cell value
				marked = True # mark the token as having been matched with a possible tag
		if (not(marked)): # if no suitable tag has been found for the token - the token has never been encountered in training
			matrix[token][most_common[0]] = sqrt(previous_max[1] * tag_probabilities[previous_max[0]][most_common[0]] * most_common[1]) # use the most common value to calculate the cell value
	return matrix

# get the sequence of tokens, their tags and probabilities
def get_sequence(matrix, tokens, tags):
	sequence = [] # the sequence is initally an empty list
	
	for i in range(len(tokens) - 1, -1, -1): # go through the tokens in reverse order
		token = tokens[i] # get the token
		tag = get_max(matrix, token, tags) # get the best tag for the token
		entry = [token] # put it in a list
		entry.append(tag[0]) # add to the entry the tag
		entry.append(tag[1]) # add to the entry its probability 
		entry = [entry] # enclose the entry in a list
		entry.extend(sequence) # add it to the current sequence
		sequence = entry # the sequence is the extended sequence
		
	return sequence

# perform the Viterbi algorithm
def viterbi(tokens, start_probabilities, word_tag_probabilities, tag_probabilities):
	tags = tag_probabilities.keys() # get the different kind of tags
	matrix = initialize_matrix(tokens, tags) # get the empty, initialized matrix
	
	matrix = calculate_first_column(matrix, tokens, tags, start_probabilities, word_tag_probabilities) # calculate the matrix's first column
	matrix = calculate_columns(matrix, tokens, tags, tag_probabilities, word_tag_probabilities) # calculate the matrix's other columns
	
	return get_sequence(matrix, tokens, tags)

#-------------------------------------------------------#
#                PERFORMANCE FUNCTIONS                  #
#-------------------------------------------------------#

# compare the words tagged by Viterbi and the original
def compare(tagged, original):
	if (len(tagged) == len(original)): # if they are of the same length
		length = len(tagged) # get the length
		correct = 0
		for i in range(0, length): # go through each tagged instance
			if (not(tagged[i][0].lower() == original[i][0].lower())):
				print("Different words: " + tagged[i][0].lower() + " and " + original[i][0].lower())
				return 0
			if (tagged[i][1] == original[i][1]): # if the word was tagged correctly
				correct += 1 # increment the number of correctly-tagged words
		return correct/length
	else:
		print("Lengths are not the same: " + str(len(tagged)) + " and " + str(len(original)));
		return 0

def ncross(n, start):
	global training_set_size
	global most_common
	test_set_size = int(training_set_size / n) # calculate the size of the test set
	performance = [] # the list of performance results
	print("Corpus Size (Documents): " + str(training_set_size))
	print("Corpus Size (Tokens): " + str(len(get_tagged_words(0, training_set_size, []))))
	print("")
	for i in range(start, n): # perform validation n times
		test_set = [j for j in range(i * test_set_size, i * test_set_size + test_set_size)] # create a list of all the documents that will make up the test set
		training_set = [j for j in range(0, training_set_size) if not (j in test_set)] # the set of training documents
		print("Test Set: " + str(test_set)) # print the test set
		print("Training Set: " + str(training_set)) # print the training set
		
		most_common = get_most_common_tag(0, training_set_size, test_set) # get the most common tag, excluding  from training the documents in the test set
		start_probabilities = initialize_start_probabilities(0, training_set_size, test_set) # calculate the probabilities that each tag starts a sentence, excluding  from training the documents in the test set
		word_tag_probabilities = initialize_word_probabilities(0, training_set_size, test_set) # calculate the probabilities that a word is associated with a particular tag, excluding  from training the documents in the test set
		tag_probabilities = initialize_tag_probabilities(0, training_set_size, test_set)  # calculate the probabilities that a tag 'i' is followed by a tag 'j', excluding  from training the documents in the test set
		
		print("Learning Process Finished")
		
		original = get_tagged_sentences(test_set[0], len(test_set), []) # get the original, tagged sentences from the test set
		sentences = [[original[j][k][0].lower() for k in range(0, len(original[j]))] for j in range(0, len(original))] # extract just the words from each sentence in the test set
		tagged = [] # initialize the set of tagged sentences to an empty list
		original = get_tagged_words(test_set[0], len(test_set), []) # update the original sentences to be just a stream of words
		
		print("Sentences Extracted")
		
		for sentence in sentences: # go through each sentence
			tagged_sentence = viterbi(sentence, start_probabilities, word_tag_probabilities, tag_probabilities) # tag the sentence
			tagged.extend(tagged_sentence) # add the tagged sentence to the list of tagged sentences
			
		print("Sentences Tagged")
		
		performance.append(compare(tagged, original)) # add to the list of performance results the latest result
		print("Correct Rate: " + str(performance[i - start] * 100) + "%") # output the test set's percentage result
		print("") # add two empty lines
	return sum(performance) / n

#-------------------------------------------------------#

n = 10
start = 7
print("N-Cross Validation (N = " + str(n) + "): " + str(ncross(n, start) * 100) + "%")

#user_input = get_input()
#while(user_input != 'quit'):
#	tokens = word_tokenize(user_input)
#	print(viterbi(tokens, start_probabilities, word_tag_probabilities, tag_probabilities))
#	user_input = get_input()
