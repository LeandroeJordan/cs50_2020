select distinct p.name from stars s join people p on s.person_id = p.id
              join movies m on s.movie_id = m.id
        where m.title like "%Toy Story%"
