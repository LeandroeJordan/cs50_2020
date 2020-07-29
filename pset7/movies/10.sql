select distinct p.name from directors d join people p on d.person_id = p.id
    join ratings r on r.movie_id = d.movie_id
where rating >= 9.0 order by 1;