Aegir HTTP basic ldap authentication
===============================

Introduction
------------

This is a simple module and drush script for Aegir that allows you to specify an
LDAP server, Require and filter for  HTTP basic authentication per site in Aegir.

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

There are two parts to the code:
- A Drupal module for hostmaster - contained in the /hosting directory. Install
  this like any other Drupal module into you hostmaster site.
- A provision Drush script - contained in the /provision directory. Copy this
  into /var/aegir/.drush/provision/aegir_http_basic_ldap/ on your Aegir master
   server.

Now just enable the module in the Aegir frontend, and you're ready to go.


Usage
-----

When creating or editing a site, you can optionally add an LDAP server, Require Filter and
message for the HTTP basic authentication. Leaving this blank will do nothing,
but if they are filled in then those requirements will be sent to the backend and
required to access the site.

Caveats
-------

This module does work in production. One should take care in an Aegir context to either build 
Aegir or install the module in the aegir site directory to avoid having it clobbered.
The provision file in .drush of your aegir root should be fine during updates.
Also, HTTP Basic authentication is sent over the internet as plain text, 
so you really shouldn't be using passwords you want to keep secret. 
Well, unless you only use ssl.
