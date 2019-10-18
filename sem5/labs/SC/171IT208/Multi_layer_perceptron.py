import pandas as pd
import numpy as np

def sigmoid(A):
	return (1/(1+np.exp(-1*A)))

def activation2(A):
	for i in range(A.shape[0]):
		if(A[i][0]>0):
			A[i][0]=1
		else:
			A[i][0]=0
	return A

def main():

	print("Using IRIS dataset")

	df1=pd.read_csv('IRIS.csv')
	#print(df1)
	df1["class"]=df1["class"].astype('category')
	df1["class_cat"]=df1["class"].cat.codes
	df1=df1.drop(columns=['class'])

	df1=df1.values#convert dataframe to numpy matrix
	np.random.shuffle(df1)
	X=df1[:,:-1]
	Y=df1[:,-1]
	I=np.ones((X.shape[0],1))
	X=np.concatenate((I,X),axis=1)
	m=X.shape[0]
	Y=Y.reshape((m,1))

	sz_test=(int)(m/10)
	sz_train=m-sz_test

	alpha=0.1
	while(alpha<=1.0):
		print("Using learning rate : ",alpha)
		precision=0
		recall=0
		accuracy=0
		fp,fn,tp,tn=0,0,0,0
		for i in range(10):
			i1=(i*sz_test)
			i2=((i+1)*sz_test)
			X_test,X_train = X[i1:i2,:],np.concatenate((X[0:i1,:],X[i2:m,:]),axis=0)
			Y_test,Y_train = Y[(i*sz_test):((i+1)*sz_test),:],np.concatenate((Y[0:i1,:],Y[i2:m,:]),axis=0)
	#X_train.shape

			W1=np.random.rand(X_train.shape[1],5)#5 is no of nodes in hidden layer
			W2=np.random.rand(5,1)
			print(W2.shape)
		#threshold=0
			
			ex_no=0
			for i in range(500):
				print("W1 : \n",W1)
				print("Training example : ",X_train[ex_no,:])
				input_layer_op=sigmoid(X_train[ex_no,:])
				hidden_layer=np.dot(input_layer_op,W1)
				print("hidden_layer : \n",hidden_layer,"\n",hidden_layer.shape)
				#a1=sigmoid(prod)
				#print("a1 : \n",a1,"\n",a1.shape)
				hidden_layer_op=sigmoid(hidden_layer)
				print("hidden layer output : \n",hidden_layer_op,"\n",hidden_layer_op.shape)
				#a=sigmoid(np.dot(X_train[ex_no,:],W1))
				output_layer=np.dot(hidden_layer,W2)
				output_layer_op=sigmoid(output_layer)
				print("output_layer : \n",output_layer_op,"\n",output_layer_op.shape)
				#print(a2.shape)
				Cost_op=output_layer_op[0]*(1-output_layer_op[0])*(1-output_layer_op[0])
				print("Output layer cost :\n",Cost_op," ",Cost_op.shape)
				#print(bb)
				Cost_hidden1=np.multiply(hidden_layer_op,(1-hidden_layer_op))
				
				print("Hidden layer cost : \n",Cost_hidden1,"\n",Cost_hidden1.shape)
				change=(alpha*J)*X_train[ex_no,:]
				change=change.reshape(X_train.shape[1],1)
			
				W=np.add(W,change)
				ex_no=(ex_no+1)%sz_train

			prod=np.dot(X_test,W)
		#print("Shape is ",prod.shape)

			a=activation2(prod)

			for i in range(a.shape[0]):
			#print(a[i]," ",Y_test[i],"\n")
				if(a[i][0]==0 and Y_test[i]==0):
					tn+=1
				elif(a[i][0]==0 and Y_test[i]==1):
					fn+=1
				elif(a[i][0]==1 and Y_test[i]==0):
					fp+=1
				elif(a[i][0]==1 and Y_test[i]==1):
					tp+=1

		#print("FP, TP, FN, TN ",fp,tp,fn,tn)

		precision=tp/(tp+fp)
		recall=tp/(tp+fn)
		accuracy=(tp+tn)/(tp+tn+fp+fn)

		precision=(float)(precision/10)
		recall=(float)(recall/10)
		accuracy=(float)(accuracy/10)
		print("Accuracy, Precision and Recall : ",accuracy," ",precision," ",recall,"\n\n")
		alpha+=0.1

	


if __name__=='__main__':
	main()
