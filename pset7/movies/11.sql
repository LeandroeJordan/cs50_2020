select m.title from stars s join people p on s.person_id = p.id
    join ratings r on r.movie_id = s.movie_id
    join movies m on m.id = s.movie_id
where p.name = "Chadwick Boseman"  order by rating desc limit 5;