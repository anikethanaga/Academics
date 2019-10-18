import pandas as pd
import numpy as np

def sigmoid(matrix):
	return 1/(1+np.exp(-1*matrix))

def main():

	files=['IRIS.csv','SPECT.csv','SPECTF.csv']

	for file in files:
		MLP(file)

def MLP(file):
		print("Using ",file," dataset")
		df1=pd.read_csv(file)
	#print(df1)
		df1["class"]=df1["class"].astype('category')
		df1["class_cat"]=df1["class"].cat.codes
		df1=df1.drop(columns=['class'])

		df1=df1.values#convert dataframe to numpy matrix
		np.random.shuffle(df1)
		X=df1[:,:-1]
		Y=df1[:,-1]
		'''I=np.ones((X.shape[0],1))
		X=np.concatenate((I,X),axis=1)'''
		m=X.shape[0]
		Y=Y.reshape((m,1))

		sz_test=(int)(m/10)
		sz_train=m-sz_test

		#print(X)

		alpha=0.1
		while(alpha<=0.1):
			print("Using learning rate : ",alpha)
			precision=0
			recall=0
			accuracy=0
			fp,fn,tp,tn=0,0,0,0
			for i in range(1):
				i1=(i*sz_test)
				i2=((i+1)*sz_test)
				X_test,X_train = X[i1:i2,:],np.concatenate((X[0:i1,:],X[i2:m,:]),axis=0)
				Y_test,Y_train = Y[(i*sz_test):((i+1)*sz_test),:],np.concatenate((Y[0:i1,:],Y[i2:m,:]),axis=0)

				n_hidden=5

				W1=np.random.rand(X_train.shape[1],n_hidden)
				b1=np.random.rand(1,n_hidden)

				W2=np.random.rand(n_hidden,1)
				b2=np.random.rand(1,1)
			
				ex_no=0
				for i in range(1):
					inp_first_layer=X_train[ex_no,:].reshape(1,X_train.shape[1])
					print(inp_first_layer)
					inp_hidden_layer=np.add(np.dot(inp_first_layer,W1),b1)
					output_hidden_layer=sigmoid(inp_hidden_layer).reshape(1,n_hidden)

					inp_last_layer=np.add(np.dot(output_hidden_layer,W2),b2)
					output_last_layer=sigmoid(inp_last_layer).reshape(1,1)

					err_last_layer = output_last_layer*(1 - output_last_layer)*(Y_train[ex_no,:] - output_last_layer)
					err_last_layer.reshape(1,1)
					err_hidden_layer = output_hidden_layer*(1 - output_hidden_layer)*np.dot(err_last_layer,np.transpose(W2))
					err_hidden_layer.reshape(1,n_hidden)
					err_input_layer = inp_hidden_layer*(1 - inp_hidden_layer)*np.dot(err_hidden_layer,np.transpose(W1))
					err_input_layer.reshape(1,X_train.shape[1])

					change_W2 = alpha*np.dot(np.transpose(output_hidden_layer),err_last_layer)
					change_W1 = alpha*np.dot(np.transpose(inp_first_layer),err_hidden_layer)
					change_b2 = alpha*err_last_layer
					change_b2.reshape(1,1)
					change_b1 = alpha*err_hidden_layer

					W1 = np.add(W1,change_W1)
					W2 = np.add(W2,change_W2)
					b1 = np.add(b1,change_b1)
					b2 = np.add(b2,change_b2)

					ex_no=(ex_no+1)%sz_train

				for j in range(X_test.shape[0]):

					inp_first_layer=X_train[j,:].reshape(1,X_train.shape[1])
					inp_hidden_layer=np.add(np.dot(inp_first_layer,W1),b1)
					output_hidden_layer=sigmoid(inp_hidden_layer).reshape(1,n_hidden)

					inp_last_layer=np.add(np.dot(output_hidden_layer,W2),b2)
					output_last_layer=sigmoid(inp_last_layer).reshape(1,1)
		#print("Shape is ",prod.shape)

					if(output_last_layer[0][0]==0 and Y_test[i]==0):
						tn+=1
					elif(output_last_layer[0][0]==0 and Y_test[i]==1):
						fn+=1
					elif(output_last_layer[0][0]==1 and Y_test[i]==0):
						fp+=1
					elif(output_last_layer[0][0]==1 and Y_test[i]==1):
						tp+=1

			print("FP, TP, FN, TN ",fp,tp,fn,tn)

			'''precision=tp/(tp+fp)
			recall=tp/(tp+fn)
			accuracy=(tp+tn)/(tp+tn+fp+fn)

			print("Accuracy, Precision and Recall : ",accuracy," ",precision," ",recall,"\n\n")'''
			break
			alpha+=0.1


if __name__=='__main__':
	main()
