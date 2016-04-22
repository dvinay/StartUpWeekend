# StartUpWeekend
Start-up Weekend desktop registration application in C++ using QT Creator.

# How to run
<ol>

<li> Download and import package into QT Creator. </li>
<li> Create SQLite Database in local with three tables
      <table>
      <tr> <td>1</td> <td>organizer(username,password)</td> </tr>
      <tr> <td>2</td> <td>users(First_name,Last_name,Phone_number,Email_id,Amount_paid,User_id,Department,Address,City,State,Zip,Notes)</td> </tr>
      <tr> <td>3</td> <td>schedule(Start_time,End_time,Topic,Date)</td> </tr>
      
</li>
<li> or you can map to Server Database by uncommenting 35th line in login.cpp</li>
<li> you can send mail to register user for confirmation(configure SMTP details in 30th line of smtp.cpp)</li>
<ol>
