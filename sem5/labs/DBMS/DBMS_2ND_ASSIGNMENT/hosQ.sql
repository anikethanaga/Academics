#Write a query in SQL to obtain the names of all patients whose primary care is taken by a physician who is not the head of any 
#department and name of that physician along with their primary care physician.

select pt.name AS "Patient",p.name AS "Primary care Physician"
FROM Patient pt
JOIN PhysicianE p ON pt.pcp=p.employeeid
WHERE pt.pcp NOT IN(select head FROM Department);



#Write a query in SQL to obtain the names of all patients who had at least two appointments where the nurse who prepped the
#appointment was a registered nurse and the physician who has carried out primary care.

select Patient.Name,PhysicianE.Name as PhysicianName from PhysicianE inner join Patient on PhysicianE.employeeid=Patient.pcp inner join Appointment on Appointment.Patient=Patient.ssn inner join Nurse on Appointment.PrepNurse=Nurse.employeeid where Nurse.Registered=1 group by Patient having count(*)>1;




#Write a query in SQL to obtain the names of all patients who have been undergone a procedure costing more than $5,000 and
#the name of that physician who has carried out primary care.

SELECT pt.name AS "Ptient",
       p.name AS "Primary Physician",
       pd.cost AS "Procedure Cost"
FROM Patient pt
JOIN Undergoes u ON u.patient=pt.ssn
JOIN PhysicianE p ON pt.pcp=p.employeeid
JOIN Procedures pd ON u.Procedures=pd.code
WHERE pd.cost>5000;


#Write a query in SQL to obtain the name of all those physicians who completed a medical procedure with certification after the
#date of expiration of their certificate, their position, procedure they have done, date of procedure, name of the patient on which
#the procedure had been applied and the date when the certification expired

select p.name as "Physician",p.position as "Position",pr.name as "procedure",u.DateUndergoes as "Date of Procedure",pt.name as "Patient",
       t.certificationexpires as "Expiry Date of Certificate"
from PhysicianE p,Undergoes u,Patient pt, Procedures pr,Trained_In t
where u.patient=pt.ssn and u.procedures=pr.code and u.physician=p.employeeid and pr.code=t.treatment
     and p.employeeid=t.physician and u.DateUndergoes>t.certificationexpires;

#Write a SQL query to obtain the names of all the physicians performed a medical procedure but they are not certified to perform.

select p.name as "Physician",pr.name as "Procedure",u.DateUndergoes,pt.name as "Patient"
from PhysicianE p,Undergoes u, Patient pt, Procedures pr
where u.patient=pt.ssn and u.Procedures=pr.code and u.physician=p.employeeid and NOT EXISTS(select *
                                                                                             from Trained_In t
                                                                                             where t.treatment=u.procedures
                                                                                             and t.physician=u.physician); 