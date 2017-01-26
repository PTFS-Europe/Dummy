<!-- Error Handling -->
[% IF whole.error %]
<!-- Dispatch on Status -->
<p>We encountered an error:</p>
<ol>
  <li>[% whole.status %]</li>
  <li>[% whole.message %]</li>
</ol>
[% END %]

[% IF whole.stage == "search_form" %]
<h2>Search a dummy request</h2>
<form method="POST" action="/cgi-bin/koha/ill/ill-requests.pl">
  <fieldset class="action">
    <input type="hidden" name="stage" value="[% whole.stage %]"/>
    <input type="hidden" name="method" value="[% whole.method %]"/>
    <input type="hidden" name="op" value="[% whole.method %]"/>
    <label for="search">Search string:</label>
    <input type="text" name="search" value="" />
    <label for="borrowernumber">Borrower number:</label>
    <input type="text" name="borrowernumber" value="" />
    <label for="branchcode">Pickup branch:</label>
    <select id="branchcode" name="branchcode">
      <option value="" />
      [% FOREACH branch IN branches %]
      <option value="[% branch.branchcode %]">
        [% branch.branchname %]
      </option>
      [% END %]
    </select>
    <label for="medium">Request type:</label>
    <select id="medium" name="medium">
      <option value="" />
      [% FOREACH medium IN media %]
      <option value="[% medium %]">[% medium %]</option>
      [% END %]
    </select>
    <input type="submit" value="Search"/>
    <a class="cancel" href="/cgi-bin/koha/ill/ill-requests.pl">Cancel</a>
  </fieldset>
</form>

[% ELSIF whole.stage == "search_results" %]
<h2>Select a dummy request</h2>
[% IF whole.value.candidates %]
<table>
  <thead>
    <tr>
      <th id="id">ID</th>
      <th id="title">Title</th>
      <th id="author">Author</th>
      <th id="select">Select?</th>
    </tr>
  </thead>
  <tbody>
    [% FOREACH candidate IN whole.value.candidates %]
    <tr>
      <td>[% candidate.id %]</td>
      <td>[% candidate.title %]</td>
      <td>[% candidate.author %]</td>
      [% target = "/cgi-bin/koha/ill/ill-requests.pl?method=" _ whole.method
                  _ "&stage=" _ whole.stage
                  _ "&borrowernumber=" _ whole.value.borrowernumber
                  _ "&branchcode=" _ whole.value.branchcode
                  _ "&medium=" _ whole.value.medium
                  _ "&id=" _ candidate.id %]
      <td><a href="[% target %]">Request this request</a></td>
    </tr>
    [% END %]
</tbody>
</table>
[% ELSE %]
<p>We have no results</p>
[% END %]

[% ELSE %]
<p>We encountered an unexpected situation</p>

[% END %]
