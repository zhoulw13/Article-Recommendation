# Article-Recommendation

##Compiler & OS
* g++
* Ubuntu 14.04  

##Process
* 1.Use tf-idf get the most representative words from all of the documents  
* 2.Use lda(Latent Dirichlet Allocation) topic model to draw realation between topics and words, documents and topics.  
* 3.Use ctr(Collaborative Topic Recommendation) to draw realtion between users and topics, and modify realation between documents and topics using collaborative filtering  

##Run
* ./lda est 8 200 settings.txt mult.txt random result/
* ./ctr 
