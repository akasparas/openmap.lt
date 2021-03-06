<Style name="interpolation">
    <Rule>
      &maxscale_zoom17;
      <LineSymbolizer>
        <CssParameter name="stroke">#888</CssParameter>
        <CssParameter name="stroke-width">1</CssParameter>
        <CssParameter name="stroke-dasharray">2,4</CssParameter>
      </LineSymbolizer>
    </Rule>
</Style>
<Style name="housenumbers">
    <Rule>
      &maxscale_zoom17;
      <TextSymbolizer name="addr:housenumber" fontset_name="book-fonts" size="9" fill="#444" dy="0" wrap_width="0"/>
    </Rule>
</Style>
<Style name="housenames">
    <Rule>
      &maxscale_zoom17;
      &minscale_zoom17;
      <TextSymbolizer name="addr:housename" fontset_name="book-fonts" size="8" fill="#444" dy="0" wrap_width="20"/>
    </Rule>
    <Rule>
      &maxscale_zoom18;
      <TextSymbolizer name="addr:housename" fontset_name="book-fonts" size="9" fill="#444" dy="0" wrap_width="20"/>
    </Rule>
</Style>
<Layer name="interpolation_lines" status="on" srs="&osm2pgsql_projection;">
     <StyleName>interpolation</StyleName>
     <Datasource>
      <Parameter name="table">
       (select way from &prefix;_line where "addr:interpolation" is not null) as interpolation
      </Parameter>
      &datasource-settings;
    </Datasource>
</Layer>
<Layer name="housenumbers" status="on" srs="&osm2pgsql_projection;">
    <StyleName>housenumbers</StyleName>
    <Datasource>
      <Parameter name="table">
      (select way,"addr:housenumber" from &prefix;_polygon where "addr:housenumber" is not null and building is not null
       union
       select way,"addr:housenumber" from &prefix;_point where "addr:housenumber" is not null
      ) as housenumbers
      </Parameter>
      &datasource-settings;
    </Datasource>
</Layer>
<Layer name="housenames" status="on" srs="&osm2pgsql_projection;">
    <StyleName>housenames</StyleName>
    <Datasource>
      <Parameter name="table">
      (select way,"addr:housename" from &prefix;_polygon where "addr:housename" is not null and building is not null
       union
       select way,"addr:housename" from &prefix;_point where "addr:housename" is not null
      ) as housenames
      </Parameter>
      &datasource-settings;
    </Datasource>
</Layer>

