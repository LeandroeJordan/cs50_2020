select distinct p.name from stars s join people p on s.person_id = p.id
       join (select s2.movie_id from stars s2 join people p2 on s2.person_id = p2.id
               where p2.name in ("Kevin Bacon") and p2.birth = 1958) kbm on kbm.movie_id = s.movie_id
        where  p.name <> "Kevin Bacon" order by p.name;