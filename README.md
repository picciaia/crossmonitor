# crossmonitor
A simple Qt forex cross monitor to use with Bitstamp
This application is an MVC-like simple tool to read Bitcon-to-EUR quotation from BitStamp service.

The Model (model.h/cpp) is composed by the cross information (cross.h/cpp) together with the URL service and the refresh period.
The Model is completely separated from the View (MainWindow.h/cpp/ui) and communicates its updates by using the Qt mechanism of SIGNALS/SLOTS. With this approach the Model can exists by knowing nothing about the View.
The View is implemented as a standard Qt window (not QML-like) and responds to the user actions (currently only the QSpinBox to modify the refresh period). 
The Controller receives the user inputs (as SIGNALS) from the view and also creates and maintains a parallel worker, implemented using a QTTimer, to access cross information in an async-like architecture that supports SIGNALS/SLOTS.
The Controller can communicate to the View by using the public method 'AddLog' to display messages and errors.
Moreover the Controller can update the Model (Cross values and update period) by using a standard c++ method (Cross_set).



						Model
					SI  /		\
					   /		 \
					  / 		  \ Method
					 /		   \	
			          SL    /                   \
				       /   SI          SL    \
	                View (MainWindow)     --------->  Controller
			*		       Method	        *
			*		    <----------		*
			*					*
			*					*
	 User interaction			      Async worker (CrossProvider)
	 
	 
	 
	 
Important note:
In order to run the application on some Windows versions, since it uses the QT object 'QNetworkAccessManager' in order to establish an SSL (HTTPS) connection to the BitStamp service, the OpenSSL DLL could be requested into the executable folder. The openssl windows binaries can be downloaded from 'https://indy.fulgan.com/SSL/' and the binaries to be copied into the application folder are 'ssleay32.dll' and 'libeay32.dll'
