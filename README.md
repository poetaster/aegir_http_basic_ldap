Aegir HTTP basic ldap authentication
===============================

Introduction
------------

This is a simple module and drush script for Aegir that allows you to specify an
LDAP server and filter for  HTTP basic authentication per site in Aegir.

Ends up adding stanzas to the vhost conf something like
<pre>
 <Directory /siteroot>
  AuthBasicProvider ldap
  AuthLDAPURL "ldap://ldap.somewhere.de/ou=users,dc=somewhere,dc=de?uid"
  AuthzLDAPAuthoritative on
  Require ldap-group cn=aegiradmins,ou=groups,dc=somewhere,dc=de
 </Directory>
</pre>


Installation
------------

The following installation of the code included is being used with Aegir 1.4 
installed from debian packages with drush 4.4. Documentation at 
http://community.aegirproject.org/installing/debian

In the main it is important to note that the provision script below includes 
a file located in the debian specific path /usr/share/drush/commands/.

There are two parts to the code:
- A Drupal module for hostmaster - contained in the /hosting directory. Install
  this like any other Drupal module into you hostmaster site. (ie.
  /platform/sites/all/modules.)

- A provision Drush script - contained in the /provision directory. Copy this
  into /var/aegir/.drush/provision/http_basic_auth_ldap.drush.inc on your 
  Aegir master server.

Now just enable the module in the Aegir frontend, and you're ready to go.


Usage
-----

When creating or editing a site, you can optionally add an LDAP server, 
Require Filter and message for the HTTP basic authentication. 
Leaving this blank will do nothing, but if they are filled in then those 
requirements will be sent to the backend and required to access the site.

Caveats
-------

This module does work in production. One should take care in an Aegir context 
to either build Aegir or install the module in the aegir site directory 
(or sites/all/modules) to avoid having it clobbered.  The provision file 
in .drush of your aegir root should be fine during updates.
Also, HTTP Basic authentication is sent over the internet as plain text, 
so you really shouldn't be using passwords you want to keep secret. 
Well, unless you only use ssl.

SSL
---

In order to support SSL so that the virtual hosts are not locked to IP 
addresses we use 4 small modifications to the drush provision scripts.

You will need to modify:
/usr/share/drush/commands/provision/http/http.ssl.inc

and the template files in:
/usr/share/drush/commands/provision/http/apache_ssl/
We include our modified versions in this repository for reference.

