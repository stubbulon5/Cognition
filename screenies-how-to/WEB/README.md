

# Troubleshooting web ssl

If trouble accessing https://harmonyframeworks.com/ because of expired certificate,

Read the following:
https://wordpress.org/support/topic/locked-out-unable-to-access-site-after-forcing-https-2/


To set certificates in bitnami + WP (on Lightsail)
```
1.) Install the  WP Encryption plugin on WP console and follow instructions to get a cert.
https://wordpress.org/plugins/wp-letsencrypt-ssl/

Now set the config:
2.) ssh to the box eg ssh bitname@123.123.123.123
3.) vi /opt/bitnami/apache2/conf/bitnami/bitnami.conf
```

then point the Cert and Certfile config values to the downloaded cert (in step 1 - which get persisted inside the Wordpress website) ie
![ssl.png](ssl.png) 


also, don't forget to copy the ca-bundle file eg (the file can be Downloaded by clicking the ca bundle button): 
![ca-bundle.png](ca-bundle.png) 


SCP the file to the host and then run
```
cp /opt/bitnami/apache2/conf/server-ca.crt /opt/bitnami/apache2/conf/server-ca.crt.old # backup
cp /home/bitnami/apps/wordpress/htdocs/keys/fullchain.crt /opt/bitnami/apache2/conf/server-ca.crt
sudo chown -R bitnami:root /opt/bitnami/apache2/conf/server-ca.crt



\

```
then restart the Web Server 

```
sudo /opt/bitnami/ctlscript.sh restart
```
# Locking down the site
Disable rest api by installing plugin, enabling
https://wordpress.org/plugins/disable-json-api/

On the settings page of the plugin (click the checkbox), allow only the  /jwt-auth/v1 relates items (/jwt-auth/v1/token and  /jwt-auth/v1/token/validate). 
This will prevent any other rest calls to the site unless they are AUTHENTICATED.

You can assert this is working by attempting:
```
curl -k https://harmonyframeworks.com/wp-json/wp/v2/users
``

you should get the messages: DRA: Only authenticated users can access the REST API

now authorize using your user and get the JWT: 
```
curl -d '{"username" : "prsrocker", "password" : ""}' \
-H "Content-Type: application/json" -X POST https://www.harmonyframeworks.com/wp-json/jwt-auth/v1/token
```

and then make an authorized call:
```
curl -k -H "Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJodHRwczpcL1wvd3d3Lmhhcm1vbnlmcmFtZXdvcmtzLmNvbSIsImlhdCI6MTU4Nzg4NTUwOCwibmJmIjoxNTg3ODg1NTA4LCJleHAiOjE1ODg0OTAzMDgsImRhdGEiOnsidX
NlciI6eyJpZCI6IjIifX19.4rVVTqzsrwg7lfkLch8w3CLgixxP6xCEy1vwuoH4euI" \
https://harmonyframeworks.com/wp-json/wp/v2/users 
``

curl -k -X POST -H "Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJodHRwczpcL1wvd3d3Lmhhcm1vbnlmcmFtZXdvcmtzLmNvbSIsImlhdCI6MTU4Nzg4OTY0MywibmJmIjoxNTg3ODg5NjQzLCJleHAiOjE1ODg0OTQ0NDMsImRhdGEiOnsidXNlciI6eyJpZCI6IjIifX19.kR4mIfen242BTWbuSBzdL0zx3HNhkazO2-hRXkr9nRk" \
https://harmonyframeworks.com/wp-json/jwt-auth/v1/token/validate




curl -k  -X POST  -d '{"username" : "prsrocker@gmail.com", "password" : "IMlV0AR0$cLvJ63k^GjtzaeT"}' \
-H "Content-Type: application/json" https://www.harmonyframeworks.com/wp-json/simple-jwt-login/v1/token/


# App interaction with the website

Done through JWT, which requires the *JWT Authentication for WP REST API* Wordpress plugin
https://en-gb.wordpress.org/plugins/jwt-authentication-for-wp-rest-api/

Follow installation instructions.

At the end, the

STEP 1: Authenticate, and get response token
```
curl -d '{"username" : "prsrocker", "password" : ""}' \
-H "Content-Type: application/json" -X POST https://www.harmonyframeworks.com/wp-json/jwt-auth/v1/token
```

STEP 2: Make authenticated call using token in the header
```

curl -k "http://harmonyframeworks.com/{some_page}"\
    -H "Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJodHRwczpcL1wvd3d3Lmhhcm1vbnlmcmFtZXdvcmtzLmNvbSIsImlhdCI6MTU4NzYyMjkxNywibmJmIjoxNTg3NjIyOTE3LCJleHAiOjE1ODgyMjc3MTcsImRhdGEiOnsidXNlciI6eyJpZCI6IjMifX19.veVp52srkpvWh0Fb7gY-UxbyhbCoK_pdHgAnHLGHD-Q" 
```



um-api's expects:
um_key to equal numerical user id
um_token to equal:

md5(um_user_secret_key+um_key)


comes from 

select * from  `wp_usermeta` where user_id = 3
and meta_key = 'um_user_secret_key'
;

ie 
$secret = get_user_meta( $user, 'um_user_secret_key', true );






WORKING SECENARIO;

if user id 3 has has the following data in wp_usermeta
um_user_secret_key = abc
um_user_public_key = zzz


then um_key = zzz
and um_token = md5(abczzz) # ie md5(um_user_secret_key+um_user_public_key)

http://harmonyframeworks.com/um-api/get.user?um_id=3&um_key=zzz&um_token=0d6fe623f2b925cf99dac45b83520748


# Cognition custom endpoints WP Plugin


## Endpoint to upsert token for user
```
curl -k -X POST -H 'Content-Type: application/json' \
-d '{ "userKey" : "user", "userToken" : "tok" }' \
https://harmonyframeworks.com/wp-json/hf_cog/v1/add_user_token
```



## Endpoint to validate Licence against user's metadata!

```
curl -k -X POST -H 'Content-Type: application/json' \
-d '{"clientApp" : "cognition", "clientAppVer" : "1.0", "userLicence" : "licVal", "userKey" : "user", "userToken" : "tok" }' \
https://harmonyframeworks.com/wp-json/hf_cog/v1/validate_licence
```