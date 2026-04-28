.mode table
.headers off
.nullvalue NULL

.mode table
.width 70 20 20

select
	*,
	case when (expected is null and observed is null)   then 'PASSED'
		when (expected is null or observed is null) then 'FAILED'
		when (expected=observed or (maxdiff is not null and abs(expected-observed)<=maxdiff)) then 'PASSED'
		else 'FAILED'
	end as result,
	case when maxdiff is not null then abs(expected-observed) end as absdiff
	from (
		select
			'geomag_decl(45.646626, 13.793812, 100, ''2026-03-14 12:00:00'')' as test_description,
			geomag_decl(45.646626, 13.793812, 100, '2026-03-14 12:00:00')     as observed,
			4.54867272425936                                                  as expected,
			1.0e-8								  as maxdiff
		union all
		select
			'geomag_decl_yc(45.646626, 13.793812, 100, ''2026-03-14 12:00:00'')' as test_description,
			geomag_decl_yc(45.646626, 13.793812, 100, '2026-03-14 12:00:00')     as observed,
			0.102306721323263                                                    as expected,
			1.0e-8								     as maxdiff
	);

