select m.title from stars s join people p on s.person_id = p.id
              join movies m on s.movie_id = m.id
        where p.name in ("Johnny Depp")  and
        m.id in
        (select m2.id from stars s2 join people p2 on s2.person_id = p2.id
              join movies m2 on s2.movie_id = m2.id where p2.name in ("Helena Bonham Carter"));